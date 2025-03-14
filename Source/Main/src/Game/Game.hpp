#ifndef GAME_HPP
#define GAME_HPP

#include <Core/Engine.h>
#include <Utils/Vector2D.h>

#include "imgui_impl_sdl2.h"

#include <memory>

#include <SQLiteCpp/SQLiteCpp.h>

class TextureManager;
class SceneManager;
class TileMap;
class Engine;

class Game {
 private:
  bool m_isvsync {};
  bool m_showImgui {};
  bool m_showImgui2 {};

  std::unique_ptr<SceneManager> m_sceneManager;

  SQLite::Database m_db;
  // std::string m_qInsert { "INSERT INTO ItemsStore (id_item, equipped, lv, "
  //                         "slot_01, slot_02, slot_03, slot_04, slot_05, slot_06)"
  //                         "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)" };

  std::string m_qGetStoreItems { "SELECT * FROM StoreItems" };

 protected:
 public:
  Game();
  ~Game();

  auto Init() -> void;

  auto Events() -> void;
  auto Update(float deltaTime) -> void;
  // auto Render() -> void;

  // https://en.cppreference.com/w/cpp/utility/functional/function
  // static std::function<void( )> dSOme;
  // static std::vector<std::function<void(std::string)>> AUpdate;

  Engine* m_engine;
};

#endif // GAME_HPP