//
// Created by cris on 9/24/24.
//

#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include "../ECS/Registry.hpp"

class CollisionSystem : public System {
 public:
  CollisionSystem();
  ~CollisionSystem();
  auto Update(float deltaTime) -> void;
};

#endif // COLLISIONSYSTEM_HPP
