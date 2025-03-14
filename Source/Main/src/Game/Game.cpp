#include "Game.hpp"

#include <Components/AnimationComponent.hpp>
#include <Components/ColliderComponent.hpp>
#include <Components/GraphicComponent.hpp>
#include <Components/RigidBodyComponent.h>
#include <Components/TransformComponent.hpp>
#include <ECS/Registry.hpp>
#include <Graphics/TextureManager.h>
#include <Input/Controller.h>
#include <Parsers/MapFileParser.hpp>
#include <Systems/AnimationSystem.hpp>
#include <Systems/CollisionSystem.hpp>
#include <Systems/MovementSystem.hpp>
#include <Systems/RenderColliderSystem.hpp>
#include <Systems/RenderSystem.hpp>
#include <Utils/Utils.hpp>

#include "../Scenes/SceneManager.hpp"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

#include <SQLiteCpp/SQLiteCpp.h>

Game::Game()
    : m_db("assets/Datas/data.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
  Logger::Debug(LogType::Log, "### Game::Constructor");
  Logger::Debug(LogType::Log, "# Game::Sqlite3");

  SQLite::Statement q_ItemsStore(m_db, m_qGetStoreItems);

  while (q_ItemsStore.executeStep()) {
    // auto id = query.getColumn(0);
    int storeItemsID = q_ItemsStore.getColumn(0).getInt();
    int storeItemsType = q_ItemsStore.getColumn(1).getInt();

    Logger::Debug(LogType::Debug, "id :", storeItemsID);

    SQLite::Statement q_listItems(
      m_db,
      "SELECT * FROM ListItems "
      "WHERE id = ?"
      "AND type = ?"
    );
    q_listItems.bind(1, storeItemsID);
    q_listItems.bind(2, storeItemsType);
    q_listItems.executeStep();

    std::string name = q_listItems.getColumn(1).getString();

    Logger::Debug(LogType::Debug, "name :", name);
    //
  }

  Logger::Debug(LogType::Log, "# Game::Sqlite3 -- OK");
}

Game::~Game() {
  // ImGui_ImplSDLRenderer2_Shutdown();
  // ImGui_ImplSDL2_Shutdown();
  // ImGui::DestroyContext();
  // if (ImGui::GetDrawData())
  //   Logger::Debug(LogType::Check, "# Engine::~Engine - ImGui::GetDrawData true");
  Logger::Debug(LogType::Log, "### Game::Destructor");
}

auto Game::Init() -> void {
  Logger::Debug(LogType::Log, "Game::Init");

  /*
   * #####################################
   * ######## SceneManager ########
   * #####################################
   */

  m_sceneManager = std::make_unique<SceneManager>();

  m_sceneManager->m_textureManager = m_engine->m_textureManager;
  m_sceneManager->m_tileMap = m_engine->m_tileMap;
  m_sceneManager->m_registry = m_engine->m_registry;

  m_sceneManager->Init();

  /*
   * #####################################
   * ######## Texture Manager ########
   * #####################################
   */

  m_engine->m_textureManager->AddTexture(
    "Player", "assets/images/Dungeon/heroes/knight/knight_idle_spritesheet.png"
  );
}

auto Game::Events() -> void { m_sceneManager->Events(); }

auto Game::Update(float deltaTime) -> void {
  // Logger::Debug(LogType::Debug, "Game::Update deltatime: ", deltaTime);

  /*
   * #####################################
   * ######## Game Update ########
   * #####################################
   */

  m_sceneManager->Update(deltaTime);
}

// auto Game::Render() -> void { m_engine->Render(); }