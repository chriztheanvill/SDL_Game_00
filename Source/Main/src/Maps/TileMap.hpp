#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <map>
#include <variant>
#include <memory>
#include <string>
#include <SDL2/SDL.h>

#include "./Tile.hpp"
// #include "./MapCollider.hpp"

enum class LevelSelect {
	Level_00,	// Debug
	Level_01,
	Level_02,
	Level_03,
	Level_04,
	Level_05,
};

/**
 * @brief Como estan ordenados los mapas
 * LevelSelect es un enum, Son los niveles
 * string son los layers del tilemap
 * Ultimo son los tiles
 */
using Maps = std::map<LevelSelect, std::vector<std::pair<std::string, std::vector<Tile>>>>;

class TileMap {
  public:
	struct MapCollider {
		std::string name { };
		SDL_Rect rect { };
	};
	using MapColls = std::map<LevelSelect, std::vector<MapCollider>>;

  private:
	LevelSelect currentLevelSelected;
	Maps m_maps;

	MapColls m_mapColls;
	// std::vector<Maps> m_maps;

	auto AddTileMapToRegistry(std::unique_ptr<class Registry>& registry, uint16_t level) -> void;
	auto AddCollMapToRegistry(std::unique_ptr<class Registry>& registry, uint16_t level) -> void;

  public:
	TileMap( );
	~TileMap( );

	// std::function<void(String)> tmp;
	// TextureManager* m_textureManager;

	// auto SetTextureManager(TextureManager* tm) -> void;
	auto ClearOtherLevels(std::unique_ptr<class Registry>& registry, uint16_t level) -> void;
	auto SelectLevel(std::unique_ptr<class Registry>& registry, uint16_t level) -> void;
	auto RemoveLevelFromECS(std::unique_ptr<class Registry>& registry, uint16_t level) -> void;

	// auto AddMap(const Maps& maps) -> void { m_maps.push_back(maps); }
	auto SetMap(const Maps& maps) -> void { m_maps = maps; }
	auto SetMapColl(const MapColls& maps) -> void { m_mapColls = maps; }
	auto SelectCurrentLevel(LevelSelect levelSelect) -> void;
	// auto Update(const float& deltaTime) -> void;
	// auto Render( ) -> void;

	// auto dSome( ) -> void;
};

#endif	 // TILEMAP_HPP
