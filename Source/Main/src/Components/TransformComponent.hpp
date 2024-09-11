#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include <utility>

#include "../Utils/Vector2D.h"

#include "../Utils/EnumComponentID.hpp"

// #include "../Utils/Logger.h"

// template <class T>
// struct TransformComponent : public Component<T>
struct TransformComponent {
  uint16_t entityID {};
  Vector2D position {};
  Vector2D scale {};
  double rotation {};

  TransformComponent(
    uint16_t entityid = 0, Vector2D pos = { 0, 0 }, Vector2D sca = { 1, 1 }, double rot = 0.0
  )
      : entityID(entityid)
      , position(std::move(pos))
      , scale(std::move(sca))
      , rotation(rot) { }

  // auto operator==(const TransformComponent& other) const -> bool = default;
  // auto operator==(const TransformComponent& other) const -> bool { return this == &other; }
  auto operator==(const TransformComponent& other) const -> bool {
    return this->entityID == other.entityID;
  }
};

#endif // TRANSFORMCOMPONENT_HPP
