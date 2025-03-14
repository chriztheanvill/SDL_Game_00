//
// Created by cris on 12/30/24.
//

#include "SceneBase.hpp"
#include "SceneManager.hpp"
#include <Systems/RenderSystem.hpp>

#include "../Actors/Player/Player.hpp"

SceneBase::SceneBase() { Logger::Debug(LogType::Log, "### SceneBase::SceneBase: "); }

SceneBase::~SceneBase() { Logger::Debug(LogType::Log, "### SceneBase::~SceneBase: "); }

auto SceneBase::LoadMap(SceneSelect sceneSelect) -> void {
  auto r = m_fileNames.at(sceneSelect);

  Logger::Debug(LogType::Log, "SceneBase::LoadLevel: ", r);

  /*
   * #####################################
   * ######## TileMaps ########
   * #####################################
   */

  m_sceneManager->m_tileMap->SetRegistry(m_sceneManager->m_registry);

  m_sceneManager->m_tileMap->SelectLevel(sceneSelect);

  /*
   * #####################################
   * ######## Actors ########
   * #####################################
   */

  // m_player = std::make_unique<Player>(m_sceneManager->m_registry);
  // m_player->Init();

  // m_gameObjects.emplace_back(std::make_unique<Player>(m_sceneManager->m_registry));

  m_enemy_01 = m_sceneManager->m_registry->NewEntity("Enemy01");

  // m_transform
  //   = new TransformComponent(m_enemy_01.GetID(), Vector2D { 100, 150 }, Vector2D { 4, 4 }, 0.0F);

  m_transform
    = TransformComponent(m_enemy_01.GetID(), Vector2D { 100, 150 }, Vector2D { 4, 4 }, 0.0F);

  m_enemy_01.AddComponent<TransformComponent>(m_transform);
  // m_enemy_01.AddComponent<TransformComponent>(Vector2D { 500, 150 }, Vector2D { 4, 4 }, 0.0F);
  m_enemy_01.AddComponent<RigidBodyComponent>(GameType::TopDown, 0);

  m_enemy_01.AddComponent<GraphicComponent>(
    "Player",
    SDL_Rect { 0, 0, 16, 16 },
    0 + std::to_underlying(GraphicComponent::SortLayer::FG),
    true,
    SDL_FLIP_NONE,
    GraphicComponent::Sprite()
  );

  m_enemy_01.AddComponent<ColliderComponent>(
    // ColliderComponent::Box(Vector2D { 0, 0 }, Vector2D { 16, 16 })
    ColliderComponent::Circle(Vector2D { 0, 0 }, 16)
  );

  m_enemy_01.AddComponent<AnimationComponent>(
    "Idle",
    std::vector<AnimationComponent::Frame> {
      { { 16 * 0, 0 }, 100 },
      { { 16 * 1, 0 }, 100 },
      { { 16 * 2, 0 }, 100 },
      { { 16 * 3, 0 }, 100 },
      { { 16 * 4, 0 }, 100 },
      { { 16 * 5, 0 }, 100 }
  }
  );

  // for (auto& gms: m_gameObjects) { gms->Init(); }

  // for (auto& gms: m_gameObjects) { gms.get().Init(); }

  // m_sceneManager->m_registry->Update();
  // m_sceneManager->m_registry->GetSystem<RenderSystem>().Sort();

  // Logger::Debug(LogType::Log, "SceneBase::LoadLevel: ", r);
}

auto SceneBase::Enter() -> void { Logger::Debug(LogType::Log, "SceneBase::Enter: "); }
auto SceneBase::Exit() -> void { Logger::Debug(LogType::Log, "SceneBase::Exit: "); }

auto SceneBase::Events() -> void { }

auto SceneBase::Update(float deltaTime) -> void {
  // Logger::Debug(LogType::Note, "SceneBase::Update");
  for (auto& gms: m_gameObjects) {
    // Logger::Debug(LogType::Note, "SceneBase::Update: ", gms->id);
    // auto ex = m_sceneManager->m_registry->GetEntity(gms->id);
    //
    // if (!ex) {
    //   Logger::Debug(LogType::Check_01, "SceneBase::Update: no value: ", ex.error());
    //   continue;
    // }
    //
    // Entity e = ex.value();
    // if (e.GetComponent<ColliderComponent>().isTrigger) {
    //   Logger::Debug(LogType::Check_01, "SceneBase::Update: collided ");
    // }

    // gms.get().Update(deltaTime);
    gms->Update(deltaTime);
  }

  if (Controller::Instance().ButtonA()) {
    if (m_btnPress) return;
    m_btnPress = true;
    Logger::Debug(LogType::Check_01, "SceneBase::Update: Button A ");

    Logger::Debug(LogType::Check_01, "m_gameObjects.size(): ", m_gameObjects.size());

    for (const auto& gms: m_gameObjects) {
      Logger::Debug(LogType::Check_01, "id: ", gms->id);
      Logger::Debug(
        LogType::Check_01, "Name: ", m_sceneManager->m_registry->GetEntity(gms->id)->GetName()
      );
    }

    Logger::Debug(LogType::Check_01, "SceneBase::Update: Button A ");

    // m_sceneManager->m_registry->RemoveEntity(m_player);
    m_sceneManager->m_registry->RemoveEntity(m_enemy_01);

    Logger::Debug(LogType::Check_01, "SceneBase::Update: Button A ");
  }
}