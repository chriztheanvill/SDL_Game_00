#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../ECS/Registry.hpp"
#include "../Graphics/TextureManager.h"

#include <SDL2/SDL.h>
#include <functional>
#include <memory>
#include <ranges>

class RenderSystem : public System {
  SDL_Renderer* m_render;
  // TextureManager* m_textureManager;
  std::shared_ptr<TextureManager>& m_textureManager;

 public:
  explicit RenderSystem(std::shared_ptr<TextureManager>& textureManager);

  /** @brief Primero sortea por YSort, despues por ZIndex.
   *
   *  YSort: Obtener el vector de entidades y "dividir" en 2,
   *  para SOLO sortear los que esten usando YSORT
   *
   *  ZIndex: Sortea por zIndex.
   */
  auto Sort() -> void;
  auto Render() -> void;

  // static std::function<void(void)> sf_Sort;
}; // RenderSystem

#endif // RENDERSYSTEM_HPP