#ifndef MAPFILEPARSER_HPP
#define MAPFILEPARSER_HPP

#include <fstream>
#include <cstdint>
#include <vector>
// #include <tuple>
#include <utility>
#include <map>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>

#include "../Utils/Logger.h"
#include "../Utils/Vector2D.h"
#include "../Maps/Tile.hpp"
#include "../Maps/TileMap.hpp"
#include "../Utils/Utils.hpp"
#include "../Graphics/TextureManager.h"

struct TileSetFile {
	int columns;
	int imageh;
	int imagew;
	int tileh;
	int tilew;
	int tilecount;
	float margin;
	float spacing;
	std::string path;
	std::string name;
	// std::vector<std::tuple<int, float>> vAnim;
	// std::map<int, std::vector<std::tuple<int, int>>> vAnim;
	std::map<int, std::vector<std::pair<int, int>>> vAnim;
};

class MapFileParser {
  private:
	TextureManager* m_textureManager;
	TileMap* m_tileMap;
	// std::map<std::string, std::vector<TileFile>> mapped;

	std::vector<TileSetFile> m_tilesetFiles;

	// Primero poner los TileSets, Luego los Mapas (levels)
	// Los Tilesets tienen que ir en orden como va en el
	// TileMap: TileSets
	std::map<LevelSelect, std::string> m_fileNames {
		// TileSets
		// std::string(FileLocations::TileMaps) + "PrtCave.json",
		// std::string(FileLocations::TileMaps) + "full spritesheet.json",
		// std::string(FileLocations::TileMaps) + "full tilemap.json",
		//
		// TileMaps (Level_XX)
		{ LevelSelect::Level_00, std::string(FileLocations::TileMaps) + "Level_00.json" },
		{ LevelSelect::Level_01, std::string(FileLocations::TileMaps) + "Level_01.json" },
	};

	auto LoadTextures( ) -> void;

	auto GetTiles(const nlohmann::json& jfile
	) -> std::vector<std::pair<std::string, std::vector<Tile>>>;
	auto GetTileSets(const nlohmann::json& jfile) -> TileSetFile;

	auto GetObjects(const nlohmann::json& jfile) -> std::vector<TileMap::MapCollider>;

  public:
	MapFileParser( );
	virtual ~MapFileParser( );

	// auto Parse( ) -> std::expected<TileMap, std::string>;
	auto Parse( ) -> std::expected<bool, std::string>;

	auto SetTextureManager(TextureManager* tm) -> void { m_textureManager = tm; }
	auto SetTileMap(std::unique_ptr<TileMap>& tileMap) -> void { m_tileMap = tileMap.get( ); }
};

#endif	 // MAPFILEPARSER_HPP
