#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../ECS/Registry.hpp"
#include "../Graphics/TextureManager.h"

#include <SDL2/SDL.h>
#include <memory>
#include <ranges>

class RenderSystem : public System {
  SDL_Renderer* m_render;
  // TextureManager* m_textureManager;
  std::shared_ptr<TextureManager>& m_textureManager;

 public:
  explicit RenderSystem(std::shared_ptr<TextureManager>& textureManager);

  auto Sort() -> void;
  auto Render() -> void;
}; // RenderSystem

#endif // RENDERSYSTEM_HPP
