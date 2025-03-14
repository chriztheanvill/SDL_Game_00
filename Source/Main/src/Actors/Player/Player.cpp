//
// Created by cris on 2/24/25.
//

#include "Player.hpp"

Player::Player(std::shared_ptr<Registry>& registry) {
  Logger::Debug(LogType::Check, "Player::Player()");
  m_registry = registry;

  m_entity = m_registry->NewEntity("Player");
  id = m_entity.GetID();
  // m_entity = m_scenarioManager->m_registry->NewEntity("Player");

  m_entity.AddComponent<TransformComponent>(Vector2D { 400, 210 }, Vector2D { 4, 4 }, 0.0F);
  // m_player.AddComponent<RigidBodyComponent>(GameType::Platformer);
  m_entity.AddComponent<RigidBodyComponent>(GameType::TopDown, 10);
  // m_player.AddComponent<RigidBodyComponent>(GameType::TopDown, 50); // orginal

  m_entity.AddComponent<GraphicComponent>(
    "Player",
    SDL_Rect { 0, 0, 16, 16 },
    -2 + std::to_underlying(GraphicComponent::SortLayer::FG),
    true,
    SDL_FLIP_NONE,
    GraphicComponent::Sprite()
  );

  m_entity.AddComponent<ColliderComponent>(
    ColliderComponent::Box(Vector2D { 0, 0 }, Vector2D { 16, 16 })
  );

  m_entity.AddComponent<AnimationComponent>(
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
}

Player::~Player() { Logger::Debug(LogType::Check, "~Player::Player()"); }

auto Player::Init() -> void { Logger::Debug(LogType::Check, "Player::Init()"); }

auto Player::Update(float deltaTime) -> void {
  // Logger::Debug(LogType::Check, "Player::Update()");
}