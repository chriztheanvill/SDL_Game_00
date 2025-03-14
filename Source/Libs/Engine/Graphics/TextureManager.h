#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SDL2/SDL_image.h>

#include <cassert>
#include <map>
#include <string>

class TextureManager {
 private:
  std::map<std::string, SDL_Texture*> m_textures;
  SDL_Renderer* m_render {};
  SDL_Window* m_window {};

 public:
  TextureManager();
  virtual ~TextureManager();

  auto AddTexture(const std::string& name = "", const std::string& path = "") -> SDL_Texture*;

  [[nodiscard]] constexpr auto GetTexture(const std::string& name = "") const -> SDL_Texture* {
    assert(!m_textures.empty() && "Textures are empty");
    assert(m_textures.contains(name) && "Texture does not exist");

    return m_textures.at(name);
  }

  constexpr void SetRender(SDL_Renderer& render) { m_render = &render; }
  constexpr void SetWindow(SDL_Window& window) { m_window = &window; }

  [[nodiscard]] constexpr auto GetRender() const -> SDL_Renderer* { return m_render; }
  [[nodiscard]] constexpr auto GetWindow() const -> SDL_Window* { return m_window; }

  auto Clear() -> void;

  std::string m_glslVersion {};
};

#endif // TEXTUREMANAGER_HPP