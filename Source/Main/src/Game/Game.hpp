#ifndef GAME_HPP
#define GAME_HPP

// #include ""
#include "../Core/Engine.h"
// #include "../Graphics/TextureManager.h"
#include "../Utils/Vector2D.h"

#include <memory>

class TextureManager;

class Game {
 private:
  bool m_isrunning {};
  bool m_isvsync {};

  std::shared_ptr<TextureManager> m_textureManager;
  std::unique_ptr<class Registry> m_registry;
  std::unique_ptr<class TileMap> m_tileMap;

  auto LoadLevel(uint16_t level) -> void;

 protected:
 public:
  Game();
  ~Game();

  auto Init() -> void;

  auto Events() -> void;
  auto Update(float deltaTime) -> void;
  auto Render(float deltaTime) -> void;

  [[nodiscard]] auto IsRunning() const -> bool { return m_isrunning; }

  auto SetTextureManager(std::shared_ptr<TextureManager>& val) -> void { m_textureManager = val; }

  // https://en.cppreference.com/w/cpp/utility/functional/function
  // static std::function<void( )> dSOme;
  // static std::vector<std::function<void(std::string)>> AUpdate;
};

#endif // GAME_HPP
