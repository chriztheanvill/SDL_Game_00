//
// Created by cris on 9/15/24.
//

#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../ECS/Registry.hpp"
#include "../Graphics/TextureManager.h"

#include <SDL2/SDL.h>
#include <memory>
#include <ranges>

class AnimationSystem : public System {
 public:
  AnimationSystem();
  ~AnimationSystem();

  auto Update(float deltaTime = 0) -> void;
};

#endif // ANIMATIONSYSTEM_HPP
