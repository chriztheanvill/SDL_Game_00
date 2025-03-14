//
// Created by cris on 2/25/25.
//

#ifndef IGAMEOBJECT_HPP
#define IGAMEOBJECT_HPP

#include <Utils/Logger.h>
#include <Utils/Utils.hpp>

class IGameObject {
 public:
  IGameObject() { }
  virtual ~IGameObject() { }

  virtual auto Init() -> void = 0;
  virtual auto Update(float deltaTime) -> void = 0;

  uint64_t id;
};

#endif // IGAMEOBJECT_HPP