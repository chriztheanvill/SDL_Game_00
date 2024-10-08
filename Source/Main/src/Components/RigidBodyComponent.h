#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include "../Utils/Logger.h"
#include "../Utils/Vector2D.h"

enum class GameType { TopDown, Platformer };

class RigidBodyComponent {
 private:
  float m_mass { 1 };
  float m_gravity { 9.8 };
  float m_speed { 1 };
  uint8_t m_time { 10 };

  Vector2D m_force { 0, 0 };
  Vector2D m_friction { 0, 0 };

  Vector2D m_position { 0, 0 };
  Vector2D m_velocity { 0, 0 };
  Vector2D m_acceleration { 0, 0 };

  GameType m_gameType = GameType::TopDown;

 public:
  uint16_t entityID {};

  RigidBodyComponent(uint16_t entityid = 0, GameType gt = GameType::TopDown, float force_t = 0.0f)
      : entityID(entityid)
      , m_gameType(gt) {
    // entityID = entityid;
    ApplyForceX(force_t);
    // Logger::Debug(LogType::Log, "RigidBody::Constructor");
  }

  // RigidBody( ) = default;
  // RigidBody(const RigidBody& other); // Copy
  // RigidBody(RigidBody&& other) noexcept; // Move
  // RigidBody& operator=(const RigidBody& other); // Copy Operator
  // RigidBody& operator=(RigidBody&& other) noexcept; // Move Operator

  // ~RigidBody( ) { Logger::Debug(LogType::Log, "~RigidBody::Destructor"); }
  ~RigidBodyComponent() = default;

  // auto operator==(const RigidBody& other) const -> bool = default;
  auto operator==(const RigidBodyComponent& other) const -> bool { return this == &other; }

  void SetMass(const float& m) { m_mass = m; }

  void SetGravity(const float& g) { m_gravity = g; }

  void SetSpeed(const float& s) { m_speed = s; }

  auto SetGameType(GameType gameType) -> void { m_gameType = gameType; }

  void ApplyForce(const Vector2D& v) { m_force = v; }

  void ApplyForceX(const float& v) { m_force.x = v; }

  void ApplyForceY(const float& v) { m_force.y = v; }

  void UnsetForce() { m_force = Vector2D::Zero(); }

  void UnsetForceX() { m_force.x = 0; }

  void UnsetForceY() { m_force.y = 0; }

  void ApplyFriction(const Vector2D& v) { m_friction = v; }

  void UnsetFriction() { m_friction = Vector2D::Zero(); }

  void Update(float deltaTime) {
    if (GameType::Platformer == m_gameType) {
      m_acceleration.x = (m_force.x + m_friction.x) / m_mass;
      m_acceleration.y = m_gravity + m_force.y / m_mass;
    } else {
      m_acceleration.x = (m_force.x + m_friction.x) / m_mass;
      m_acceleration.y = (m_force.y + m_friction.y) / m_mass;
    }

    m_velocity = m_acceleration * deltaTime;
    // m_velocity = (m_acceleration * deltaTime) * m_speed;
    // m_velocity = (m_acceleration * deltaTime) * m_time;
    m_position = m_velocity * deltaTime;

    // m_position *= 100000.0f;
  }

  [[nodiscard]] auto Mass() const -> const float& { return m_mass; }

  [[nodiscard]] auto Gravity() const -> const float& { return m_gravity; }

  [[nodiscard]] auto Speed() const -> const float& { return m_speed; }

  [[nodiscard]] auto Position() const -> const Vector2D& { return m_position; }

  [[nodiscard]] auto Velocity() const -> const Vector2D& { return m_velocity; }

  [[nodiscard]] auto Acceleration() const -> const Vector2D& { return m_acceleration; }

  [[nodiscard]] auto Force() const -> const Vector2D& { return m_force; }

  [[nodiscard]] auto GetGameType() const -> GameType { return m_gameType; }
};

#endif // RIGIDBODYCOMPONENT_HPP
