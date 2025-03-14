#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <utility>

#include "../Utils/Vector2D.h"
#include "./ComponentBase.hpp"

#include "../Utils/EnumComponentID.hpp"

// #include "../Utils/Logger.h"

// template <class T>
// struct TransformComponent : public Component<T>
struct TransformComponent : public ComponentBase {
  Vector2D position {};
  Vector2D scale {};
  double rotation {};

  TransformComponent() { }

  TransformComponent(
    uint64_t entityID_t = 0, Vector2D pos = { 0, 0 }, Vector2D sca = { 1, 1 }, double rot = 0.0
  )
      : ComponentBase(entityID_t, ComponentIndex::Transform)
      , position(std::move(pos))
      , scale(std::move(sca))
      , rotation(rot) { }

  TransformComponent(
    uint64_t entityID_t = 0, std::optional<TransformComponent> other = std::nullopt
  )
      : ComponentBase(entityID_t, ComponentIndex::Transform)
      , position(std::move(other->position))
      , scale(std::move(other->scale))
      , rotation(other->rotation) { }

  // TransformComponent(uint64_t entityID_t = 0, TransformComponent* other = nullptr)
  //     : ComponentBase(entityID_t, ComponentIndex::Transform)
  //     , position(std::move(other->position))
  //     , scale(std::move(other->scale))
  //     , rotation(other->rotation) { }

  // TransformComponent(const TransformComponent&) = default;

  // TransformComponent(const TransformComponent&& other)
  //     : position(other.position)
  //     , scale(other.scale)
  //     , rotation(other.rotation) { }

  // auto operator==(const TransformComponent& other) const -> bool = default;
  // auto operator==(const TransformComponent& other) const -> bool { return this == &other; }
  // auto operator==(const TransformComponent& other) const -> bool {
  //   return this->entityID == other.entityID;
  // }
};

#endif // TRANSFORMCOMPONENT_HPP