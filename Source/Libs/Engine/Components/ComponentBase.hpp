#ifndef COMPONENTBASE_HPP
#define COMPONENTBASE_HPP

#include <cstdint>
#include <string>

enum class ComponentIndex {
  Transform,
  RigidBody,
  Collider,
  Graphic,
  // Sprite,
  // Tile,
  Animation,
};

struct ComponentBase {
  uint64_t entityID {};
  ComponentIndex componentIndex {};
};

#endif // COMPONENTBASE_HPP