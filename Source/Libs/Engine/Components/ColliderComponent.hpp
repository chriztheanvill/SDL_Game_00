//
// Created by cris on 9/24/24.
//

#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include <variant>

#include "../Utils/Vector2D.h"
#include "./ComponentBase.hpp"

struct ColliderComponent : public ComponentBase {
  struct Shape {
    Vector2D offset;

    Shape(Vector2D offset_t = Vector2D::Zero())
        : offset(offset_t) { }
  };

  struct Box : public Shape {
    Vector2D size;

    Box(Vector2D offset_t = Vector2D::Zero(), Vector2D size_t = Vector2D::Zero())
        : Shape(offset_t)
        , size(size_t) { }
  };

  struct Circle : public Shape {
    float radius;

    Circle(Vector2D offset_t = Vector2D::Zero(), float radius_t = 0.0f)
        : Shape(offset_t)
        , radius(radius_t) { }
  };

  std::variant<Box, Circle> shape;
  bool isTrigger { false };
  bool oneShoot { false };
  float waitTime { 0.0f };

  ColliderComponent(
    uint64_t entityID_t = 0,
    std::variant<Box, Circle> shape_t = Box(Vector2D::Zero(), Vector2D::Zero())
  )
      : ComponentBase(entityID_t, ComponentIndex::Collider)
      , shape(shape_t) { }
};

#endif // COLLIDERCOMPONENT_HPP