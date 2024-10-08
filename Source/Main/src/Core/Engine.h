#ifndef ENGINE_H
#define ENGINE_H

// #include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "../Utils/Logger.h"

class Engine {
 public:
  Engine();
  ~Engine();

  auto GetMainWindow() -> SDL_Window* { return m_window; }

  auto GetMainRender() -> SDL_Renderer* { return m_render; }

  auto Init() -> bool;
  auto InitGraphics(bool isVSync = false) -> bool;

 private:
  SDL_Window* m_window;
  SDL_Renderer* m_render;

  int m_windowH;
  int m_windowW;

  // SDL_Surface* m_imgIconSurface;
};

#endif // ENGINE_H
