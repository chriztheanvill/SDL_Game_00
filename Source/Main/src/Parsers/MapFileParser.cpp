#include "MapFileParser.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.h"
#include "../Components/TileComponent.hpp"

#include <algorithm>
#include <ranges>
#include <functional>

namespace views = std::ranges::views;
namespace ranges = std::ranges;

using json = nlohmann::json;

/* TODO:
 * Remove old commented code at the end of the file
 */

MapFileParser::MapFileParser( ) {}

MapFileParser::~MapFileParser( ) {}

auto MapFileParser::Parse( ) -> std::expected<bool, std::string> {
	// for (auto n : std::views::all(m_fileNames) |	  //
	// 				  std::views::take(5) |	  //  Muestra los primeros 5
	// 				  std::views::drop(2))	 // Quita  los primeros 2
	// 	Logger::Debug(LogType::Log, "Ranges: ", n);

	// ranges::for_each(m_fileNames |	 //
	// 							  views::drop(1) |	  //
	// 							  views::take(1),
	// 						  [](const std::string& i) { return i.empty( ); });

	// for (const auto& v : m_fileNames | views::filter(check_file_location))
	// {
	// 	std::cout << "\nfor: " << v << "\n";
	// }

	std::map<LevelSelect, nlohmann::json> vJsonFiles;

	auto check_file_location = [](const auto& mapFiles) {
		//
		std::ifstream ifsFile(std::string(mapFiles.second).c_str( ));
		if (!ifsFile.is_open( )) {
			Logger::Debug(
			  LogType::Error,
			  "MapFileParser::Parse::check_file_location Cant open! ",
			  mapFiles.second
			);
			return false;
		}
		ifsFile.close( );
		return true;
	};

	// auto append_new_json_file = [&vJsonFiles](auto& mapFiles)
	auto append_new_json_file
	  = [&vJsonFiles](std::pair<LevelSelect, std::string> mapFiles) -> void {
		Logger::Debug(
		  LogType::Log,
		  "MapFileParser::Parse::append_new_json_file: file num: ",
		  static_cast<int>(mapFiles.first)
		  //   typeid(mapFiles).name( )
		);
		Logger::Debug(
		  LogType::Log,
		  "MapFileParser::Parse::append_new_json_file: filename: ",
		  mapFiles.second
		);

		std::ifstream ifsFile(std::string(mapFiles.second).c_str( ));
		nlohmann::json jsonFile = json::parse(ifsFile);	  // ifsFile >> jFile;
		if (jsonFile["type"].empty( )) {
			Logger::Debug(
			  LogType::Error,
			  "MapFileParser::Parse::append_new_json_file Error "
			  "parsing a Tiled file ",
			  mapFiles.second
			);
			exit(1);
		}
		ifsFile.close( );

		std::string tmpnameslash
		  = mapFiles.second.substr(mapFiles.second.find_last_of('/') + 1, mapFiles.second.size( ));

		std::string tmpname = tmpnameslash.substr(0, tmpnameslash.find('.'));

		// Logger::Debug(LogType::Error, "append_new_json_file: info: ",
		// jsonFile);

		vJsonFiles.emplace(mapFiles.first, jsonFile);
	};

	ranges::for_each(m_fileNames | views::filter(check_file_location), append_new_json_file);

	// ####################################################
	// ####################################################

	if (vJsonFiles.empty( )) {
		Logger::Debug(LogType::Error, "MapFileParser::Parse( ) empty vJsonFiles");
		return std::unexpected("MapFileParser::Parse() empty vJsonFiles");
	}

	Maps maps;

	TileMap::MapColls mapColls;

	// auto each_json_file = [&](auto& mapFile)   //
	auto each_json_file = [&](const std::pair<LevelSelect, nlohmann::json>& mapFile) {
		// Logger::Debug(LogType::Warning, "each_json_file! ", mapFile.second);
		// 			  jfile["orientation"].get<std::string>( ));

		/* NOTE: Get TileSets */
		ranges::for_each(
		  mapFile.second["tilesets"]   //
			| views::filter([](const nlohmann::json& check) { return !check.empty( ); })
			| views::transform([](const nlohmann::json& check) {
				  return check["source"].get<std::string>( );
			  }),
		  [&](const nlohmann::json& fileNames) {
			  // Logger::Debug(
			  // LogType::Log,
			  // "+++++++++++++++++ fileNames: ",
			  // fileNames
			  // );

			  /* For lambdas + templates */
			  // Logger::Debug(LogType::Log, "", fileNames["source"].template
			  // get<std::string>());

			  std::string filename = std::string(FileLocations::TileMaps) + std::string(fileNames);

			  // Logger::Debug(
			  // LogType::Log,
			  // "+++++++++++++++++ filename trim: ",
			  // filename
			  // );
			  std::ifstream ifsFile(filename);

			  if (!ifsFile.is_open( )) {
				  Logger::Debug(
					LogType::Error,
					"MapFileParser::Ranges::each_json_file Cant open! "
				  );
				  exit(1);
			  }

			  // -----------------------------------------------------------------
			  nlohmann::json tmpjfile = json::parse(ifsFile);
			  // ifsFile >> tmpjfile;
			  if (tmpjfile["type"].empty( )) {
				  Logger::Debug(
					LogType::Error,
					"MapFileParser::Ranges::each_json_file Error parsing a "
					"Tiled file "
				  );
				  exit(1);
			  }

			  ifsFile.close( );

			  m_tilesetFiles.emplace_back(GetTileSets(tmpjfile));
		  }
		);

		/* TODO: Get Tiles */
		maps.emplace(mapFile.first, GetTiles(mapFile.second));
		mapColls.emplace(mapFile.first, GetObjects(mapFile.second));

		/* VIEWS */
		// for (const auto& v :
		// 	 jfile["tilesets"] | views::filter(
		//   [](nlohmann::json& lambdaTilesets)
		// 					{ return !lambdaTilesets.empty( ); }))
		// {
		// 	Logger::Debug(LogType::Log,
		// 				  "MapFileParser::for ",
		// 				  v["source"].get<std::string>( ));
		// }
	};

	ranges::for_each(
	  vJsonFiles | views::filter([](auto& mapFile) {
		  // Logger::Debug(
		  // LogType::Log,
		  // "MapFileParser::ParseLevel::checkif ",
		  // mapFile.second["tilesets"].empty( )
		  // );
		  if (!mapFile.second["tilesets"].empty( )) return true;
		  Logger::Debug(
			LogType::Check,
			"MapFileParser::ParseLevel::checkif The file does not contain "
			"tilesets, is empty!!! : ",
			static_cast<int>(mapFile.first)
		  );
		  return false;
	  }),
	  each_json_file
	);

	if (maps.empty( )) {
		Logger::Debug(LogType::Check, "MapFileParser::ParseLevel::each_json_file maps is empty");

		return std::unexpected("MapFileParser::ParseLevel::each_json_file maps is empty");
	}

	// m_tileMap->AddMap(maps);
	m_tileMap->SetMap(maps);
	m_tileMap->SetMapColl(mapColls);

	return true;
}

auto MapFileParser::GetTiles(const nlohmann::json& jfile
) -> std::vector<std::pair<std::string, std::vector<Tile>>> {
	std::vector<std::pair<std::string, std::vector<Tile>>> tilesChunk;

	bool infinite = jfile["infinite"].get<bool>( );
	int screenSizeH { };
	int screenSizeW { };

	if (!infinite) {
		screenSizeH = jfile["height"].get<int>( );
		screenSizeW = jfile["width"].get<int>( );
	} else {
		screenSizeH = 16;
		screenSizeW = 16;
	}

	/* ################################################################## */
	/* ################################################################## */
	/* Get Layer info */
	/* Chunks */
	auto onlyChunks
	  = [&](const nlohmann::json& checktilelayer) { return checktilelayer.contains("chunks"); };

	ranges::for_each(
	  jfile["layers"] | views::filter(onlyChunks),
	  [&](const nlohmann::json& eachLayerInfo) {
		  // Logger::Debug(LogType::Log, "eachLayerInfo: ",
		  // eachLayerInfo["properties"][0]["value"]);
		  // Logger::Debug(LogType::Log, "eachLayerInfo: ", eachLayerInfo);

		  int chunkId = eachLayerInfo["id"].get<int>( );
		  std::string chunkName = eachLayerInfo["name"].get<std::string>( );

		  float chunkOpacity = eachLayerInfo["opacity"].get<float>( );

		  float chunkStartX = eachLayerInfo["startx"].get<float>( );
		  float chunkStartY = eachLayerInfo["starty"].get<float>( );
		  // float chunkW = eachLayerInfo["width"].get<float>( );
		  // float chunkH = eachLayerInfo["height"].get<float>( );
		  // float chunkX = eachLayerInfo["x"].get<float>( );
		  // float chunkY = eachLayerInfo["y"].get<float>( );
		  bool chunkVisible = eachLayerInfo["visible"].get<bool>( );

		  int chunkOrder = 0;
		  if (eachLayerInfo.contains("properties"))
			  chunkOrder = eachLayerInfo["properties"][0]["value"].get<int>( );

		  // int chunkcounter { };

		  for (const auto& eachChunk : eachLayerInfo["chunks"]) {
			  // Logger::Debug(LogType::Log, "--------------- eachChunk ---------------");
			  int tileHeight = eachChunk["height"].get<int>( );
			  int tileWidth = eachChunk["width"].get<int>( );

			  int tileX = eachChunk["x"].get<int>( );
			  int tileY = eachChunk["y"].get<int>( );

			  int chunkOffsetX = tileX * tileWidth;
			  int chunkOffsetY = tileY * tileHeight;

			  // ++chunkcounter;
			  int tileSeparation = 0;
			  int tilecounter { };
			  std::vector<Tile> tiles;
			  for (const int eachTile : eachChunk["data"]) {
				  // Logger::Debug(LogType::Log, "eachTile: ", eachTile);
				  int tileposX = (tileWidth + tileSeparation) * (tilecounter % screenSizeW);
				  int tileposY = (tileHeight + tileSeparation) * (tilecounter / screenSizeH);

				  tilecounter++;
				  if (eachTile == 0) continue;

				  int sumtilecount { };
				  int id_original { };
				  std::vector<int> animTime;
				  std::vector<std::pair<int, int>> anims;
				  TileSetFile tileSetFile { };
				  for (auto& tileset : m_tilesetFiles) {
					  // sum = (eachTile - 1) - tileset.tilecount;
					  // sum = tileset.tilecount - (eachTile - 1);

					  sumtilecount += tileset.tilecount;
					  int sumLow = sumtilecount - tileset.tilecount;
					  // if (sumtilecount < eachTile) continue;
					  // int sum = sumtilecount - eachTile;
					  // Logger::Debug(
					  // LogType::Log,
					  // "GetMap::tileset tilecount: ",
					  // tileset.tilecount
					  // );
					  // Logger::Debug(LogType::Log, "GetMap::sum: ",
					  // sum);

					  // if (tileset.tilecount <= sum)
					  // if (sum < 0) continue;
					  if (eachTile >= sumLow && eachTile <= sumtilecount) {
						  id_original = (eachTile - 1) - (sumtilecount - tileset.tilecount);

						  if (tileset.vAnim.contains(id_original)) {
							  // Logger::Debug(
							  // LogType::Log,
							  // "Has animation: ",
							  // id_original
							  // );

							  auto currentVector = tileset.vAnim.at(id_original);

							  for (const auto [idAnim, dur] : currentVector) {
								  int srcAnimW = idAnim % tileset.columns;
								  srcAnimW *= tileset.tilew;

								  int srcAnimH = idAnim / tileset.columns;
								  srcAnimH *= tileset.tileh;

								  animTime.emplace_back(dur);
								  anims.emplace_back(srcAnimW, srcAnimH);
							  }

							  // ranges::copy(
							  // currentVector,
							  // std::back_inserter(anims)
							  // );
						  }

						  tileSetFile = tileset;
						  break;
					  }
				  }

				  if (tileSetFile.columns == 0) {
					  Logger::Debug(LogType::Error, "GetMap::columns are ZERO");
					  Logger::Debug(LogType::Debug, " GetMap::eachTile: ", eachTile);
					  // Logger::Debug(LogType::Debug, " GetMap::sum: ", sum);
					  exit(1);
				  }

				  int id = id_original - 0;

				  int srcW = id % tileSetFile.columns;
				  srcW *= tileSetFile.tilew;

				  int srcH = id / tileSetFile.columns;
				  srcH *= tileSetFile.tileh;

				  float scale = 4;
				  // float scale = 4; //  Original

				  //
				  tiles.emplace_back(
					Vector2D { static_cast<float>(tileWidth), static_cast<float>(tileHeight) },
					Vector2D { static_cast<float>(srcW), static_cast<float>(srcH) },
					Vector2D { static_cast<float>(tileposX) + chunkOffsetX,
							   static_cast<float>(tileposY) + chunkOffsetY },
					Vector2D { scale, scale },
					tileSetFile.name,
					id,
					chunkId,
					chunkOrder,
					chunkOpacity,
					chunkStartX,
					chunkStartY,
					chunkVisible,
					anims,
					animTime
				  );
			  }	  // for data
			  tilesChunk.emplace_back(chunkName, tiles);
		  }	  // for chunks
		  // map.push_back(tilesChunk);
	  }
	);

	return tilesChunk;
}	// ParseLevel

auto MapFileParser::GetObjects(const nlohmann::json& jfile) -> std::vector<TileMap::MapCollider> {
	std::vector<TileMap::MapCollider> returnValue;

	auto onlyChunks = [&](const nlohmann::json& checktilelayer) {
		return checktilelayer["type"] == "objectgroup";
	};

	ranges::for_each(
	  jfile["layers"] | views::filter(onlyChunks),
	  [&](const nlohmann::json& eachLayerInfo) {
		  const uint16_t offsetX = eachLayerInfo["x"].get<int>( );
		  const uint16_t offsetY = eachLayerInfo["y"].get<int>( );

		  for (const auto& eachObject : eachLayerInfo["objects"]) {
			  // Logger::Debug(LogType::Log, "eachObject: ", eachObject);
			  TileMap::MapCollider mapColl;
			  mapColl.name = eachObject["name"].get<std::string>( );
			  mapColl.rect = { static_cast<int>(eachObject["x"].get<float>( )) + offsetX,
							   static_cast<int>(eachObject["y"].get<float>( )) + offsetY,
							   static_cast<int>(eachObject["width"].get<float>( )),
							   static_cast<int>(eachObject["height"].get<float>( )) };

			  returnValue.push_back(mapColl);
		  }
	  }
	);

	if (returnValue.empty( )) {
		Logger::Debug(LogType::Warning, "MapFileParser::GetObjects no return value");
	}

	return returnValue;
}

auto MapFileParser::GetTileSets(const nlohmann::json& jfile) -> TileSetFile {
	// Logger::Debug(LogType::Debug, "MapFileParser::ParseTile! ", jfile);

	TileSetFile tile;
	std::string tmppath = jfile["image"].get<std::string>( );

	std::string tmpcrop = tmppath.substr(tmppath.find('/'), tmppath.size( ));
	std::string path = "assets" + tmpcrop;

	tile.path = path;
	// -----------------------------------
	std::string name = jfile["name"].get<std::string>( );
	tile.name = name;

	tile.imagew = jfile["imagewidth"].get<int>( );
	tile.imageh = jfile["imageheight"].get<int>( );
	tile.tilew = jfile["tilewidth"].get<int>( );
	tile.tileh = jfile["tileheight"].get<int>( );
	tile.tilecount = jfile["tilecount"].get<int>( );
	tile.columns = jfile["columns"].get<int>( );
	tile.spacing = jfile["spacing"].get<float>( );
	tile.margin = jfile["margin"].get<float>( );

	m_textureManager->AddTexture(tile.name, path);

	if (!jfile.contains("tiles")) return tile;

	// Get Tiles with Animations
	ranges::for_each(jfile["tiles"], [&tile](nlohmann::json otherTiles) {
		// Logger::Debug(LogType::Log, "otherTiles ", otherTiles);
		std::vector<std::pair<int, int>> vtmpanim;
		ranges::for_each(otherTiles["animation"], [&vtmpanim](nlohmann::json anim) {
			std::pair<int, int> tmpanim { anim["tileid"].get<int>( ),
										  anim["duration"].get<int>( ) };
			vtmpanim.emplace_back(tmpanim);
		});
		tile.vAnim.emplace(otherTiles["id"].get<int>( ), vtmpanim);
	});

	return tile;
}
