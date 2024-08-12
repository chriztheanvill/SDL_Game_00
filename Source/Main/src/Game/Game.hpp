#ifndef GAME_HPP
#define GAME_HPP

// #include ""
#include "../Graphics/TextureManager.h"
#include "../Core/Engine.h"
#include "../Core/Time.h"
#include "../Utils/Vector2D.h"

#include <memory>

class Game {
private:
  bool m_isrunning;

  Cris::Time m_time;

  // SDL_Event m_event;

  Engine m_engine;

  std::unique_ptr<class TextureManager> m_textureManager;
  std::unique_ptr<class Registry> m_registry;
  std::unique_ptr<class TileMap> m_tileMap;

  auto LoadLevel(const uint16_t& level) -> void;

protected:
public:
  Game( );
  ~Game( );

  auto Init( ) -> void;

  auto Events( ) -> void;
  auto Update( ) -> void;
  auto Render( ) -> void;

  [[nodiscard]] auto IsRunning( ) const -> bool { return m_isrunning; }
  auto SetRender(SDL_Renderer& render) -> void { m_textureManager->SetRender(render); }

  [[nodiscard]] auto GetTimer( ) -> Cris::Time& { return m_time; };

  // https://en.cppreference.com/w/cpp/utility/functional/function
  // static std::function<void( )> dSOme;
  // static std::vector<std::function<void(std::string)>> AUpdate;
};

#endif	 // GAME_HPP
