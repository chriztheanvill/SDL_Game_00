#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include <variant>

#include "../Utils/Utils.hpp"
#include "./Tile.hpp"
// #include "./MapCollider.hpp"

struct grid {
  int width;
  int height;
  int cellSize;
  int cellCount;
  int cellX;
  int cellY;
};

/**
 * @brief Como estan ordenados los mapas
 * LevelSelect es un enum, Son los niveles
 * string son los layers del tilemap
 * Ultimo son los tiles
 */
using Maps = std::map<SceneSelect, std::vector<std::pair<std::string, std::vector<Tile>>>>;

class TileMap {
 public:
  class Registry* m_registry;
  struct MapCollider {
    std::string name {};
    SDL_Rect rect {};
  };
  using MapColls = std::map<SceneSelect, std::vector<MapCollider>>;

 private:
  SceneSelect currentLevelSelected;
  Maps m_maps;

  MapColls m_mapColls;

  auto AddTileMapToRegistry(SceneSelect) -> void;
  auto AddCollMapToRegistry(SceneSelect) -> void;

 public:
  TileMap();
  ~TileMap();

  // std::function<void(String)> tmp;
  // TextureManager* m_textureManager;
  auto SetRegistry(std::shared_ptr<class Registry>& registry) { m_registry = registry.get(); }
  auto ClearOtherLevels(SceneSelect) -> void;
  auto SelectLevel(SceneSelect) -> void;
  auto RemoveLevelFromECS(SceneSelect) -> void;

  auto SetMap(const Maps& maps) -> void { m_maps = maps; }
  auto SetMapColl(const MapColls& maps) -> void { m_mapColls = maps; }
  auto SelectCurrentScenario(SceneSelect levelSelect) -> void;
  // auto dSome( ) -> void;
};

#endif // TILEMAP_HPP