#ifndef ENGINE_H
#define ENGINE_H

#include <memory>

#include "../Core/Time.h"
#include "../Utils/Logger.h"
#include "Core.hpp"

// #include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

class Registry;
class TileMap;

class Game;

class Engine {
 private:
  bool m_isrunning {};
  bool m_isDebugMode {};

  Core m_core;

  bool m_isVsync {};

  ImGuiIO m_io;

  auto Serialize() -> void;

 public:
  // __attribute__((visibility("default"))) Engine(); // Shared Lib
  Engine();
  // __attribute__((visibility("default"))) ~Engine();
  ~Engine();

  auto Init() -> void;
  auto Events() -> void;
  auto Update(float) -> void;
  auto Render() -> void;

  [[nodiscard]] auto GetIsRunning() const -> bool { return m_isrunning; }

  Cris::Time m_time;
  std::shared_ptr<class TextureManager> m_textureManager;
  std::shared_ptr<Registry> m_registry;
  std::shared_ptr<TileMap> m_tileMap;

  ImGuiContext* m_currentContext;

  std::unique_ptr<Game> m_game;
};

#endif // ENGINE_H