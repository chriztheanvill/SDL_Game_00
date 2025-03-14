//
// Created by cris on 12/29/24.
//

#include "Scene00.hpp"
#include "SceneManager.hpp"

#include "../Actors/Player/Player.hpp"

Scene00::Scene00() { Logger::Debug(LogType::Log, "Scene00::Scene00: "); }

Scene00::~Scene00() { Logger::Debug(LogType::Log, "Scene00::~Scene00: "); }

auto Scene00::Enter() -> void {
  Logger::Debug(LogType::Check, "Scene00::Enter: ");

  /*
   * #####################################
   * ######## TileMap ########
   * #####################################
   */

  LoadMap(SceneSelect::Scene_00);

  /*
   * #####################################
   * ######## ECS ########
   * #####################################
   */

  // m_player = std::make_unique<Player>(m_sceneManager->m_registry);
  // m_player->Init();
  // //
  // m_gameObjects.emplace_back(*m_player);

  // Player pl(m_sceneManager->m_registry);

  m_gameObjects.push_back(std::make_unique<Player>(m_sceneManager->m_registry));

  // m_player = m_sceneManager->m_registry->NewEntity("Player");
  //
  // m_player.AddComponent<TransformComponent>(Vector2D { 400, 210 }, Vector2D { 4, 4 }, 0.0F);
  // // m_player.AddComponent<RigidBodyComponent>(GameType::Platformer);
  // m_player.AddComponent<RigidBodyComponent>(GameType::TopDown, 10);
  // // m_player.AddComponent<RigidBodyComponent>(GameType::TopDown, 50); // orginal
  //
  // m_player.AddComponent<GraphicComponent>(
  //   "Player",
  //   SDL_Rect { 0, 0, 16, 16 },
  //   -2 + std::to_underlying(GraphicComponent::SortLayer::FG),
  //   true,
  //   SDL_FLIP_NONE,
  //   GraphicComponent::Sprite()
  // );
  //
  // m_player.AddComponent<ColliderComponent>(
  //   ColliderComponent::Box(Vector2D { 0, 0 }, Vector2D { 16, 16 })
  // );
  //
  // m_player.AddComponent<AnimationComponent>(
  //   "Idle",
  //   std::vector<AnimationComponent::Frame> {
  //     { { 16 * 0, 0 }, 100 },
  //     { { 16 * 1, 0 }, 100 },
  //     { { 16 * 2, 0 }, 100 },
  //     { { 16 * 3, 0 }, 100 },
  //     { { 16 * 4, 0 }, 100 },
  //     { { 16 * 5, 0 }, 100 }
  // }
  // );

  // -------------------------------------
  // -------------------------------------

  // m_enemy_01 = m_sceneManager->m_registry->NewEntity("Enemy01");
  //
  // m_enemy_01.AddComponent<TransformComponent>(Vector2D { 500, 150 }, Vector2D { 4, 4 }, 0.0F);
  // m_enemy_01.AddComponent<RigidBodyComponent>(GameType::TopDown, 0);
  //
  // m_enemy_01.AddComponent<GraphicComponent>(
  //   "Player",
  //   SDL_Rect { 0, 0, 16, 16 },
  //   0 + std::to_underlying(GraphicComponent::SortLayer::FG),
  //   true,
  //   SDL_FLIP_NONE,
  //   GraphicComponent::Sprite()
  // );
  //
  // m_enemy_01.AddComponent<ColliderComponent>(
  //   // ColliderComponent::Box(Vector2D { 0, 0 }, Vector2D { 16, 16 })
  //   ColliderComponent::Circle(Vector2D { 0, 0 }, 16)
  // );
  //
  // m_enemy_01.AddComponent<AnimationComponent>(
  //   "Idle",
  //   std::vector<AnimationComponent::Frame> {
  //     { { 16 * 0, 0 }, 100 },
  //     { { 16 * 1, 0 }, 100 },
  //     { { 16 * 2, 0 }, 100 },
  //     { { 16 * 3, 0 }, 100 },
  //     { { 16 * 4, 0 }, 100 },
  //     { { 16 * 5, 0 }, 100 }
  // }
  // );
}

auto Scene00::Exit() -> void {
  Logger::Debug(LogType::Check, "Scene00::Exit: ");

  // m_player.DisableComponent<GraphicComponent>();
}

// auto Scene00::Update(float deltaTime) -> void {
//   SceneBase::Update(deltaTime);
//   // Logger::Debug(LogType::Check_01, "Scene00::Update -- ");
//
//   // ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Once);
//   // ImGui::SetNextWindowPos(ImVec2(200, 50), ImGuiCond_Once);
//   // ImGui::Begin("aaaaa", NULL, ImGuiWindowFlags_None);
//   // ImGui::Text("aaaaaa");
//   // ImGui::End();
//
//   // if (Controller::Instance().ButtonA()) {
//   //   if (m_btnPress) return;
//   //   m_btnPress = true;
//   //   Logger::Debug(LogType::Check_01, "Scene00::Update: Button A ");
//   //
//   //   // m_sceneManager->m_registry->RemoveEntity(m_player);
//   //   m_sceneManager->m_registry->RemoveEntity(m_enemy_01);
//   //
//   //   // m_sceneManager->m_registry->Print();
//   // }
//   //
//   // if (Controller::Instance().ButtonB()) {
//   //   if (m_btnPress) return;
//   //   m_btnPress = true;
//   //   Logger::Debug(LogType::Check_01, "Scene00::Update: Button B: ", m_enemy_01.GetID());
//   //
//   //   // m_sceneManager->m_registry->RemoveEntity(m_player);
//   //   std::expected<std::reference_wrapper<Entity>::type, std::string> e
//   //     = m_sceneManager->m_registry->GetEntity(m_enemy_01.GetID());
//   //
//   //   assert(e || !fprintf(stderr, e.error().c_str()));
//   //   auto entity = e.value();
//   //
//   //   Logger::Debug(LogType::Check_01, "Scene00::Update: EnemyGet ", entity.GetID());
//   //
//   //   // m_sceneManager->m_registry->Print();
//   // }
//
//   // Logger::Debug(LogType::Check_01, "Scene00::Update: ");
//   // m_sceneManager->SwitchScenario(ScenarioSelect::Scenario_01);
// }

// Entity enemy02 = m_sceneManager->m_registry->NewEntity("Enemy02");
//
// enemy02.AddComponent<TransformComponent>(Vector2D { 520, 215 }, Vector2D { 4, 4 }, 0.0F);
// enemy02.AddComponent<RigidBodyComponent>(GameType::TopDown, 0);
//
// enemy02.AddComponent<GraphicComponent>(
//   "Player",
//   SDL_Rect { 0, 0, 16, 16 },
//   -4 + std::to_underlying(GraphicComponent::SortLayer::FG),
//   true,
//   SDL_FLIP_NONE,
//   GraphicComponent::Sprite()
// );
//
// enemy02.AddComponent<ColliderComponent>(
//   ColliderComponent::Box(Vector2D { 0, 0 }, Vector2D { 16, 16 })
// );
//
// enemy02.AddComponent<AnimationComponent>(
//   "Idle",
//   std::vector<AnimationComponent::Frame> {
//     { { 16 * 0, 0 }, 100 },
//     { { 16 * 1, 0 }, 100 },
//     { { 16 * 2, 0 }, 100 },
//     { { 16 * 3, 0 }, 100 },
//     { { 16 * 4, 0 }, 100 },
//     { { 16 * 5, 0 }, 100 }
// }
// );
//
// Entity enemy03 = m_sceneManager->m_registry->NewEntity("Enemy03");
//
// enemy03.AddComponent<TransformComponent>(Vector2D { 500, 160 }, Vector2D { 4, 4 }, 0.0F);
// enemy03.AddComponent<RigidBodyComponent>(GameType::TopDown, -50);
//
// enemy03.AddComponent<GraphicComponent>(
//   "Player",
//   SDL_Rect { 0, 0, 16, 16 },
//   -2 + std::to_underlying(GraphicComponent::SortLayer::FG),
//   true,
//   SDL_FLIP_NONE,
//   GraphicComponent::Sprite()
// );
//
// enemy03.AddComponent<ColliderComponent>(ColliderComponent::Circle(Vector2D { 0, 0 }, 4));
//
// enemy03.AddComponent<AnimationComponent>(
//   "Idle",
//   std::vector<AnimationComponent::Frame> {
//     { { 16 * 0, 0 }, 100 },
//     { { 16 * 1, 0 }, 100 },
//     { { 16 * 2, 0 }, 100 },
//     { { 16 * 3, 0 }, 100 },
//     { { 16 * 4, 0 }, 100 },
//     { { 16 * 5, 0 }, 100 }
// }
// );

// -------------------------------------
// -------------------------------------

// AnimationComponent a = player.GetComponent<AnimationComponent>();
// Logger::Debug(LogType::Log, "Player animname ");

// player.GetComponent<RigidBodyComponent>().get().ApplyFriction({ 1, 0 });

// player.RemoveComponent<SpriteComponent>( );
// player.DisableComponent<SpriteComponent>( );