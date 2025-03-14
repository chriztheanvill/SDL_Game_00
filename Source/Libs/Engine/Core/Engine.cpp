#include "Engine.h"

#include "../ECS/Registry.hpp"
#include "../Graphics/TextureManager.h"

#include "../Components/AnimationComponent.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../Components/GraphicComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.hpp"
#include "../Input/Controller.h"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/RenderColliderSystem.hpp"
#include "../Systems/RenderSystem.hpp"

#include "../Parsers/MapFileParser.hpp"

#include "../../Main/src/Game/Game.hpp"

#include "imgui.h"
#include "imgui_impl_sdlrenderer2.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

Engine::Engine()
    : m_textureManager(std::make_shared<TextureManager>())
    , m_registry(std::make_shared<Registry>())
    , m_tileMap(std::make_shared<TileMap>()) {
  Logger::Debug(LogType::Log, "### Engine::Engine");

  /*
   * #####################################
   * ######## Time ########
   * #####################################
   */

  // m_isVsync = true;
  m_isVsync = false;

  m_time.SetVSync(m_isVsync);

  /*
   * #####################################
   * ######## Core ########
   * #####################################
   */

  Logger::Debug(LogType::Log, "# Engine::Engine - Init Core");

  assert(m_core.Init() || !fprintf(stderr, "Cant load SDL2 framework, INIT \n"));
  assert(
    m_core.InitGraphics(m_isVsync) || !fprintf(stderr, "Cant load SDL2 framework, INIT Graphics \n")
  );

  Logger::Debug(LogType::Log, "# Engine::Engine - Init Core - OK");

  /*
   * #####################################
   * ######## TextureManager ########
   * #####################################
   */

  Logger::Debug(LogType::Log, "# Engine::Engine - Init TextureManager");

  m_textureManager->SetRender(*m_core.GetMainRender());
  m_textureManager->SetWindow(*m_core.GetMainWindow());
  m_textureManager->m_glslVersion = m_core.GetGLSLVersion();

  Logger::Debug(LogType::Log, "# Engine::Engine - Init TextureManager - OK");

  /*
   * #####################################
   * ######## IMGUI ########
   * #####################################
   */

  Logger::Debug(LogType::Log, "# Engine::Engine - Init IMGUI");

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  // ImGui::SetCurrentContext(ImGui::GetCurrentContext());
  m_io = ImGui::GetIO();
  (void)m_io;
  m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(m_textureManager->GetWindow(), m_textureManager->GetRender());
  ImGui_ImplSDLRenderer2_Init(m_textureManager->GetRender());

  // m_currentContext = ImGui::GetCurrentContext();
  // ImGui::SetCurrentContext(m_currentContext);
  ImGui::SetCurrentContext(ImGui::GetCurrentContext());

  // if (rr) {
  //   Logger::Debug(LogType::Debug, "Game::Init() --------------- ");
  //   Logger::Debug(LogType::Debug, "Game::Init() --------------- ");
  //   Logger::Debug(LogType::Debug, "Game::Init() --------------- ");
  //   // ImGui_ImplSDL2_ProcessEvent(&mEvent);
  // } else {
  //   Logger::Debug(LogType::Error, "Game::Init() --------------- ");
  //   Logger::Debug(LogType::Error, "Game::Init() --------------- ");
  //   Logger::Debug(LogType::Error, "Game::Init() --------------- ");
  // }

  // Controller::Instance().SetImGuiContext(ImGui::GetCurrentContext());

  Logger::Debug(LogType::Log, "# Engine::Engine - Init IMGUI - OK");

  /*
   * #####################################
   * ######## Deserialize ########
   * #####################################
   */

  Logger::Debug(LogType::Log, "# Engine::Engine - Init Deserialize Info");

  Serialize();

  Logger::Debug(LogType::Log, "# Engine::Engine - Init Deserialize Info - OK");

  /*
   * #####################################
   * ######## Registry ########
   * #####################################
   */

  Logger::Debug(LogType::Log, "# Engine::Engine - Init Registry");

  m_registry->AddSystem<MovementSystem>();
  m_registry->AddSystem<CollisionSystem>();
  m_registry->AddSystem<RenderSystem>(m_textureManager);
  m_registry->AddSystem<RenderColliderSystem>(m_textureManager->GetRender());
  m_registry->AddSystem<AnimationSystem>();

  Logger::Debug(LogType::Log, "# Engine::Engine - Init Registry - OK");

  /*
   * #####################################
   * ######## Input ########
   * #####################################
   */
  Logger::Debug(LogType::Log, "# Engine::Engine - Init Controller");
  Controller::Instance().Detect();

  Logger::Debug(LogType::Log, "# Engine::Engine - Init Controller - OK");
  /*
   * #####################################
   * ######## Registry ########
   * #####################################
   */
  m_registry->Update();
  // m_registry->GetSystem<RenderSystem>().Sort();

  m_isrunning = true;
  Logger::Debug(LogType::Log, "# Engine::Engine - DONE !!!");
}

Engine::~Engine() {
  // if (m_core.GetMainRender())
  //   Logger::Debug(LogType::Check, "# Engine::~Engine - m_core.GetMainRender() true");
  // // ImGui_ImplSDLRenderer2_Shutdown();
  // ImGui_ImplSDL2_Shutdown();
  // ImGui::DestroyContext();

  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  Logger::Debug(LogType::Log, "### Engine::Destructor");
}

auto Engine::Init() -> void {
  //

  m_game->m_engine = this;

  /*
   * #####################################
   * ######## Game Init ########
   * #####################################
   */
  m_game->Init();
}

auto Engine::Events() -> void {
  Controller::Instance().Events();
  m_isrunning = Controller::Instance().GetIsRunning();

  if (Controller::Instance().KeyPressed(SDL_SCANCODE_G)) m_isDebugMode = !m_isDebugMode;

  /*
   * #####################################
   * ######## Game events ########
   * #####################################
   */
  m_game->Events();
}

auto Engine::Update(float deltaTime) -> void {
  /*
   * #####################################
   * ######## ImGui System ########
   * #####################################
   */

  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  // Logger::Debug(LogType::Check_01, "Game::Update -- ");

  /*
   * #####################################
   * ######## ImGui ########
   * #####################################
   */
  ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiCond_Once);
  ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_Once);
  ImGui::Begin("Hello, world!", NULL, ImGuiWindowFlags_None);
  ImGui::Text("01");
  ImGui::Text("02");
  ImGui::End();

  /*
   * #####################################
   * ######## Input Controller ########
   * #####################################
   */
  Controller::Instance().Detect();

  /*
   * #####################################
   * ######## Registry Update Systems ########
   * #####################################
   */

  m_registry->GetSystem<MovementSystem>().Update(deltaTime);
  m_registry->GetSystem<CollisionSystem>().Update(deltaTime);
  m_registry->GetSystem<AnimationSystem>().Update(deltaTime);

  /*
   * #####################################
   * ######## Game Update ########
   * #####################################
   */

  m_game->Update(deltaTime);

  /*
   * #####################################
   * ######## Registry ########
   * #####################################
   */

  m_registry->Update();
}

auto Engine::Render() -> void {
  /*
   * #####################################
   * ######## ImGui ########
   * #####################################
   */

  ImGui::Render();

  /*
   * #####################################
   * ######## SDL clear color ########
   * #####################################
   */

  // Paint bg color
  SDL_SetRenderDrawColor(m_textureManager->GetRender(), 60, 60, 60, 255);
  SDL_RenderClear(m_textureManager->GetRender());

  /*
   * #####################################
   * ######## Render Game ########
   * #####################################
   */

  m_registry->GetSystem<RenderSystem>().Render();

  if (m_isDebugMode) m_registry->GetSystem<RenderColliderSystem>().Render();

  /*
   * #####################################
   * ######## Clean the screen (SDL2 / ImGui) ########
   * #####################################
   */

  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_textureManager->GetRender());
  SDL_RenderPresent(m_textureManager->GetRender());
}

auto Engine::Serialize() -> void {
  Logger::Debug(LogType::Log, "# Tilemaps");
  m_tileMap->SetRegistry(m_registry);

  MapFileParser mapFileParser;
  mapFileParser.SetTextureManager(m_textureManager.get());
  mapFileParser.SetTileMap(m_tileMap);

  const std::expected<bool, std::string>& maps = mapFileParser.Parse();
  assert(maps || !fprintf(stderr, "Cant load TileMap: %s\n", maps.error().c_str()));

  Logger::Debug(LogType::Log, "# Tilemaps - OK");
}

//
// IMGUI_CHECKVERSION();
// ImGui::CreateContext();
// // ImGui::SetCurrentContext(ImGui::GetCurrentContext());
// m_io = ImGui::GetIO();
// (void)m_io;
// m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
// m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
//
// // Setup Dear ImGui style
// ImGui::StyleColorsDark();
// // ImGui::StyleColorsLight();
//
// // Setup Platform/Renderer backends
// ImGui_ImplSDL2_InitForSDLRenderer(m_textureManager->GetWindow(),
// m_textureManager->GetRender()); ImGui_ImplSDLRenderer2_Init(m_textureManager->GetRender());
//

// auto* rr = ImGui::GetCurrentContext();
// if (rr) {
//   Logger::Debug(LogType::Debug, "Game::Init() --------------- ");
//   Logger::Debug(LogType::Debug, "Game::Init() --------------- ");
//   Logger::Debug(LogType::Debug, "Game::Init() --------------- ");
//   // ImGui_ImplSDL2_ProcessEvent(&mEvent);
// } else {
//   Logger::Debug(LogType::Error, "Game::Init() --------------- ");
//   Logger::Debug(LogType::Error, "Game::Init() --------------- ");
//   Logger::Debug(LogType::Error, "Game::Init() --------------- ");
// }
//
// Controller::Instance().SetImGuiContext(ImGui::GetCurrentContext());

// ==========================

// ImGui_ImplSDL2_InitForOpenGL(m_textureManager->GetWindow(), m_textureManager->GetRender());
// ImGui_ImplOpenGL3_Init(m_textureManager->m_glslVersion.c_str());

// ImGui_ImplOpenGL3_Init("#version 330");

// ImGui::Render();
// glViewport(0, 0, (int)m_io.DisplaySize.x, (int)m_io.DisplaySize.y);
// // glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
// // glClear(GL_COLOR_BUFFER_BIT);
// ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// SDL_GL_SwapWindow(m_textureManager->GetWindow());