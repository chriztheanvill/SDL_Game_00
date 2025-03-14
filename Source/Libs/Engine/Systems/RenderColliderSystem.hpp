//
// Created by cris on 2/15/25.
//

#ifndef RENDERCOLLIDERSYSTEM_HPP
#define RENDERCOLLIDERSYSTEM_HPP

#include "../ECS/Registry.hpp"
#include "../Graphics/TextureManager.h"

#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <ranges>

class RenderColliderSystem : public System {
  SDL_Renderer* m_render;

 public:
  RenderColliderSystem(SDL_Renderer*);

  auto Render() -> void;
};

#endif // RENDERCOLLIDERSYSTEM_HPP