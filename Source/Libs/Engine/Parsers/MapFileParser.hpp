#ifndef MAPFILEPARSER_HPP
#define MAPFILEPARSER_HPP

#include <cstdint>
#include <fstream>
#include <vector>
// #include <tuple>
#include <map>
#include <string>
#include <string_view>
#include <utility>

#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

#include "../Graphics/TextureManager.h"
#include "../Maps/Tile.hpp"
#include "../Maps/TileMap.hpp"
#include "../Utils/Logger.h"
#include "../Utils/Utils.hpp"
#include "../Utils/Vector2D.h"

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
  // std::shared_ptr<TextureManager> m_textureManager;
  TileMap* m_tileMap;
  // std::map<std::string, std::vector<TileFile>> mapped;

  std::vector<TileSetFile> m_tilesetFiles;

  // Los Tilesets tienen que ir en orden como va en el
  std::map<SceneSelect, std::string> m_fileNames {
    { SceneSelect::Scene_00, std::string(FileLocations::TileMaps) + "Level_00.json" },
    { SceneSelect::Scene_01, std::string(FileLocations::TileMaps) + "Level_01.json" },
  };

  auto LoadTextures() -> void;

  auto GetTiles(const nlohmann::json& jfile)
    -> std::vector<std::pair<std::string, std::vector<Tile>>>;
  auto GetTileSets(const nlohmann::json& jfile) -> TileSetFile;

  auto GetObjects(const nlohmann::json& jfile) -> std::vector<TileMap::MapCollider>;

 public:
  MapFileParser();
  virtual ~MapFileParser();

  // auto Parse( ) -> std::expected<TileMap, std::string>;
  auto Parse() -> std::expected<bool, std::string>;

  auto SetTextureManager(TextureManager* tm) -> void { m_textureManager = tm; }

  // auto SetTextureManager(std::shared_ptr<TextureManager>& tm) -> void { m_textureManager = tm; }

  auto SetTileMap(std::shared_ptr<TileMap>& tileMap) -> void { m_tileMap = tileMap.get(); }
};

#endif // MAPFILEPARSER_HPP