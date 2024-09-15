#include "Game.hpp"

#include "../ECS/Registry.hpp"
#include "../Graphics/TextureManager.h"
#include "../Parsers/MapFileParser.hpp"
#include "../Utils/Utils.hpp"
//
#include "../Systems/MovementSystem.hpp"
#include "../Systems/RenderSystem.hpp"
//
#include "../Components/AnimationComponent.hpp"
#include "../Input/Controller.h"

#include "../Components/GraphicComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.hpp"
#include "../Systems/AnimationSystem.hpp"

// #include "../Game/TileMap.hpp"

// std::vector<std::function<void(std::string)>> Collectable::AUpdate;
// std::function<void( )> Game::dSOme = { };

Game::Game()
    : m_isrunning(false)
    // , m_textureManager(std::make_unique<TextureManager>())
    , m_registry(std::make_unique<Registry>())
    , m_tileMap(std::make_unique<TileMap>()) {
  Logger::Debug(LogType::Log, "### Game::Constructor :");

  // m_isvsync = true;

  // AUpdate.clear(); // Works
  // Logger::Debug(LogType::Error,"Collectable entered Amount: ", AUpdate.size());
  // for (auto &a : AUpdate) {  a("999");  } // No funciona
  // for (auto a : AUpdate) { (*a)("999"); }

  // m_textureManager->SetRender(*m_engine.GetMainRender());
  // Controller::Instance( )->Detect( );
  Controller::Instance().Detect();
}

Game::~Game() { Logger::Debug(LogType::Log, "### Game::Destructor :"); }

auto Game::Init() -> void {
  /*
   * #####################################
   * ######## Texture Manager ########
   * #####################################
   */
  m_textureManager->AddTexture(
    "Player", "assets/images/Dungeon/heroes/knight/knight_idle_spritesheet.png"
  );

  /*
   * #####################################
   * ######## Maps ########
   * #####################################
   */

  MapFileParser mapFileParser;
  // m_mapFileParser.SetTextureManager(m_textureManager);
  mapFileParser.SetTextureManager(m_textureManager.get());

  mapFileParser.SetTileMap(m_tileMap);
  const std::expected<bool, std::string>& maps = mapFileParser.Parse();
  // if (!m_maps)
  assert(maps || !fprintf(stderr, "Cant load TileMap: %s\n", maps.error().c_str()));

  m_tileMap->SetRegistry(m_registry);
  LoadLevel(0);

  m_isrunning = true;
}

auto Game::LoadLevel(uint16_t level) -> void {
  Logger::Debug(LogType::Check, "Game::LoadLevel00 ", level);

  /*
   * #####################################
   * ######## ECS ########
   * #####################################
   */

  m_registry->AddSystem<MovementSystem>();
  m_registry->AddSystem<RenderSystem>(m_textureManager);
  m_registry->AddSystem<AnimationSystem>();
  // m_registry->AddSystem<RenderTileMapSystem>(m_textureManager);

  // m_registry->AddSystem<RenderSystem>(m_textureManager);
  // m_registry->AddSystem<RenderTileMapSystem>(m_textureManager);

  Entity player = m_registry->NewEntity("Player");

  player.AddComponent<TransformComponent>(Vector2D { 52, 52 }, Vector2D { 4, 4 }, 0.0F);
  // player.AddComponent<RigidBodyComponent>(GameType::Platformer);
  player.AddComponent<RigidBodyComponent>(GameType::TopDown);
  player.AddComponent<GraphicComponent>(
    "Player",
    SDL_Rect { 0, 0, 16, 16 },
    -4 + std::to_underlying(GraphicComponent::SortLayer::FG),
    SDL_FLIP_NONE,
    GraphicComponent::Sprite()
  );

  player.AddComponent<AnimationComponent>(std::vector<AnimationComponent::Frame> {
    { { 16 * 0, 0 }, 100 },
    { { 16 * 1, 0 }, 100 },
    { { 16 * 2, 0 }, 100 },
    { { 16 * 3, 0 }, 100 },
    { { 16 * 4, 0 }, 100 },
    { { 16 * 5, 0 }, 100 }
  });

  // player.GetComponent<RigidBodyComponent>().get().ApplyFriction({ 1, 0 });

  // player.RemoveComponent<SpriteComponent>( );
  // player.DisableComponent<SpriteComponent>( );

  m_tileMap->SelectLevel(level);

  m_registry->Update();
}

auto Game::Events() -> void {
  Controller::Instance().Events();
  m_isrunning = Controller::Instance().GetIsRunning();
}

auto Game::Update(float deltaTime) -> void {
  /* ################################################# */
  Controller::Instance().Detect();
  m_registry->GetSystem<MovementSystem>().Update(deltaTime);
  m_registry->GetSystem<AnimationSystem>().Update(deltaTime);

  /* ################################################# */

  m_registry->Update();
}

auto Game::Render(float deltaTime) -> void {
  // Paint bg color
  SDL_SetRenderDrawColor(m_textureManager->GetRender(), 60, 60, 60, 255);
  SDL_RenderClear(m_textureManager->GetRender());

  /* ################################################# */

  // Delta time en render es para las animaciones
  m_registry->GetSystem<RenderSystem>().Render(deltaTime);

  /* ################################################# */

  // Clean the screen
  SDL_RenderPresent(m_textureManager->GetRender());
}
