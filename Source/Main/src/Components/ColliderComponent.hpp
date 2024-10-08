//
// Created by cris on 9/24/24.
//

#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include <variant>

#include "../Utils/Vector2D.h"

struct ColliderComponent {
  struct Shape { };

  struct Box : public Shape {
    Box(Vector2D size_t = Vector2D::Zero())
        : size(size_t) { }
    Vector2D size;
  };

  struct Circle : public Shape {
    Circle(float radius_t = 0.0f)
        : radius(radius_t) { }
    float radius;
  };

  uint16_t entityID;
  Vector2D position;
  Vector2D offset;
  std::variant<Box, Circle> shape;

  ColliderComponent(
    uint16_t entityID_t,
    Vector2D position_t = Vector2D::Zero(),
    Vector2D offset_t = Vector2D::Zero(),
    std::variant<Box, Circle> shape_t = Box(Vector2D::Zero())
  )
      : entityID(entityID_t)
      , position(position_t)
      , offset(offset_t)
      , shape(shape_t) { }
};

#endif // COLLIDERCOMPONENT_HPP
