//
// Created by cris on 12/22/24.
//

#ifndef CORE_HPP
#define CORE_HPP

// #include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "../Utils/Logger.h"

class Core {
 public:
  Core();
  ~Core();
  auto GetMainWindow() -> SDL_Window* { return m_window; }
  auto GetMainRender() -> SDL_Renderer* { return m_render; }
  auto GetMainContext() -> SDL_GLContext& { return m_context; }
  auto GetGLSLVersion() -> const char* { return m_glsl_version; }

  auto Init() -> bool;
  auto InitGraphics(bool isVSync = false) -> bool;

 private:
  SDL_Window* m_window;
  SDL_Renderer* m_render;
  SDL_GLContext m_context;
  const char* m_glsl_version;

  int m_windowH;
  int m_windowW;

  // SDL_Surface* m_imgIconSurface;
};

#endif // CORE_HPP