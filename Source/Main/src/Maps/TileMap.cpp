#include "TileMap.hpp"

#include <ranges>
#include <algorithm>

using std::ranges::find_if;
using std::ranges::for_each;
// using std::ranges::remove;
using std::ranges::views::filter;

#include <SDL2/SDL.h>

#include "../Graphics/TextureManager.h"
#include "../Utils/Logger.h"

#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/TileComponent.hpp"
#include "../Systems/RenderTileMapSystem.hpp"

namespace views = std::ranges::views;
namespace ranges = std::ranges;

TileMap::TileMap( ) {
	//
	// Game::dSOme = std::bind(&TileMap::dSome, this);
	// tmp = std::bind(&UIEquipment::UpdateLabel, this, std::placeholders::_1);
	// Collectable::AUpdate.emplace_back(&tmp);

	// Collectable::AUpdate.emplace_back(
	//     std::bind(&UIEquipment::UpdateLabel, this, std::placeholders::_1));
	//
	// Se auto llama, emitiendo "Empty"
	// std::bind(&UIEquipment::UpdateLabel, this, "Empty"));
	Logger::Debug(LogType::Log, "TileMap::TileMap: ");
}

TileMap::~TileMap( ) {
	// auto it = std::find(Collectable::AUpdate.begin(), //
	//                       Collectable::AUpdate.end(),   //
	//                       &tmp);

	//   auto itRe = Collectable::AUpdate.erase( //
	//       std::remove(                        //
	//           Collectable::AUpdate.begin(),   //
	//           Collectable::AUpdate.end(),
	//           *it //
	//           ),
	//       Collectable::AUpdate.end());
	Logger::Debug(LogType::Log, "~TileMap::TileMap: ");
}

auto TileMap::SelectCurrentLevel(LevelSelect levelSelect) -> void {
	currentLevelSelected = levelSelect;
}

auto TileMap::SelectLevel(uint16_t level) -> void {
	// Logger::Debug(LogType::Check, "TileMap::SelectLevel 0 ");
	if (!m_registry->HasSystem<RenderTileMapSystem>( )) return;
	// Logger::Debug(LogType::Log, "TileMap::SelectLevel 1 ");

	ClearOtherLevels(level);
	AddTileMapToRegistry(level);
	AddCollMapToRegistry(level);
}

auto TileMap::ClearOtherLevels(uint16_t level) -> void {
	m_registry->Update( );

	Logger::Debug(LogType::Check, "TileMap::ClearOtherLevels level: ", level);

	for (Entity& entity : m_registry->GetSystem<RenderTileMapSystem>( )->GetEntities( )
							| views::filter([&](const Entity& entity) -> bool {
								  return entity.GetComponent<TileComponent>( ).level != level
										 || !entity.HasComponent<TileComponent>( );
							  })) {
		Logger::Debug(LogType::Log, "TileMap::ClearOtherLevels Entity: ", entity.GetID( ));
		// entity.RemoveComponent<TileComponent>( );
		// entity.RemoveComponent<TransformComponent>( );
		m_registry->RemoveComponent<TileComponent>(entity);
		m_registry->RemoveComponent<TransformComponent>(entity);
		//
		m_registry->GetSystem<RenderTileMapSystem>( )->RemoveEntity(entity);
		m_registry->UpdateNumEntities(-1);
	}
}

auto TileMap::RemoveLevelFromECS(uint16_t level) -> void {
	m_registry->Update( );

	//  Logger::Debug(
	// LogType::Check,
	// "TileMap::RemoveLevelFromECS: ",
	// registry->GetSystem<RenderTileMapSystem>( )->GetEntities( ).size( ) == 0 ?
	//   " ----------------- Zero" :
	//   " +++++++++++++++++ Ya tiene algo"
	//  );

	for (Entity& entity : m_registry->GetSystem<RenderTileMapSystem>( )->GetEntities( )) {
		if (!entity.HasComponent<TileComponent>( )) continue;
		if (entity.GetComponent<TileComponent>( ).level != level) continue;
		// Logger::Debug(LogType::Log, "TileMap::RemoveLevelFromECS Entity: ", entity.GetID( ));

		// auto tmp = entity.GetComponent<TileComponent>( );
		// Logger::Debug(LogType::Log, "TileMap------ otherId: ", tmp.entityID);

		// entity.RemoveComponent<TileComponent>( );
		// entity.RemoveComponent<TransformComponent>( );
		//
		m_registry->RemoveComponent<TileComponent>(entity);
		m_registry->RemoveComponent<TransformComponent>(entity);
		//
		m_registry->GetSystem<RenderTileMapSystem>( )->RemoveEntity(entity);
		m_registry->UpdateNumEntities(-1);
	}
}

auto TileMap::AddCollMapToRegistry(uint16_t level) -> void {
	// Logger::Debug(LogType::Check, "TileMap::AddCollMapToRegistry m_mapColls: ");

	for (const auto& [levelselect, vecs] : m_mapColls) {
		// Logger::Debug(
		//   LogType::Check,
		//   "TileMap::AddCollMapToRegistry level: ",
		//   static_cast<int>(levelselect)
		// );
		if (static_cast<int>(levelselect) != level) continue;
		for (const auto& eachVec : vecs) {
			// Logger::Debug(
			//   LogType::Check,
			//   "TileMap::AddCollMapToRegistry eachVec: ",
			//   eachVec.rect.y
			// );
			// Entity collTile = registry->NewEntity(
			// 	  "tile_" + eachTile.name + "_" + std::to_string(eachTile.id)
			// 	);

			// 	collTile.AddComponent<TransformComponent>(
			// 	  Vector2D { eachTile.dst.x, eachTile.dst.y },
			// 	  Vector2D { eachTile.scale.x, eachTile.scale.y },
			// 	  0
			// 	);

			// 	collTile.AddComponent<TileComponent>(
			// 	  eachTile.name,
			// 	  eachTile.id,
			// 	  level,
			// 	  SDL_Rect { static_cast<int>(eachTile.src.x),
			// 				 static_cast<int>(eachTile.src.y),
			// 				 static_cast<int>(eachTile.size.x),
			// 				 static_cast<int>(eachTile.size.y) }
			// 	);
		}
	}
}

auto TileMap::AddTileMapToRegistry(uint16_t level) -> void {
	// Logger::Debug(LogType::Log, "TileMap::SelectLevel 2 ");
	// std::pair<std::string, std::vector<Tile>>

	for (const auto& [levelselect, vecs] : m_maps) {
		// Logger::Debug(
		//   LogType::Log,
		//   "TileMap::SelectLevel levelSelect ",
		//   static_cast<int>(levelselect)
		// );

		if (static_cast<int>(levelselect) != level) continue;

		for (const auto& [name, tiles] : vecs) {
			// Logger::Debug(LogType::Log, "TileMap::SelectLevel TileName ", name);
			for (const auto& eachTile : tiles) {
				// Logger::Debug(LogType::Log, "TileMap::SelectLevel eachTile ", eachTile.name);
				// Logger::Debug(LogType::Log, "TileMap::SelectLevel eachTile ", eachTile.id);

				Entity tile = m_registry->NewEntity(
				  "tile_" + eachTile.name + "_" + std::to_string(eachTile.id)
				);

				tile.AddComponent<TransformComponent>(
				  Vector2D { eachTile.dst.x, eachTile.dst.y },
				  Vector2D { eachTile.scale.x, eachTile.scale.y },
				  0
				);

				tile.AddComponent<TileComponent>(
				  eachTile.name,
				  eachTile.id,
				  level,
				  0,
				  SDL_Rect { static_cast<int>(eachTile.src.x),
							 static_cast<int>(eachTile.src.y),
							 static_cast<int>(eachTile.size.x),
							 static_cast<int>(eachTile.size.y) }
				);

			}	// for each tile
		}	// for each map
	}	// for maps

	// RemoveLevelFromECS(registry, level);

	// Logger::Debug(LogType::Check, "TileMap::SelectLevel After");
}

/**
	| std::ranges::views::filter(
							  [&](const Entity& entity) -> bool
							  {
								  // Logger::Debug(
								  // LogType::Log,
								  // "Each Entity level: ",
								  // entity.GetComponent<TileComponent>( ).assetId
								  // );
								  // Logger::Debug(
								  // LogType::Log,
								  // "Each Entity level: ",
								  // entity.GetComponent<TileComponent>( ).level
								  // );

								  if (!entity.HasComponent<TileComponent>( )) return false;
								  return entity.GetComponent<TileComponent>( ).level == level;
							  }
							)
*/

/**
auto TileMap::Update(const float& deltaTime) -> void
{
	auto& eachLayer = maps[currentLevelSelected];
	ranges::for_each(
	  eachLayer,
	  [&](auto& mapFiles)
	  {
		  // const std::string& nameLayer = mapFiles.first;
		  // std::vector<Tile>& tiles = mapFiles.second;
		  // Logger::Debug(LogType::Log, "TileMap::Render: ", nameLayer);
		  for (Tile& tile : mapFiles.second
							  | views::filter([](const Tile& eachTile)
											  { return !eachTile.animations.empty( ); }))
		  {
			  // if (tile.animations.empty( )) { continue; }
			  // tile.Update(deltaTime);
			  int frame = (SDL_GetTicks( ) / tile.animationsTime[0]) % tile.animationsAmount;

			  tile.src.x = static_cast<float>(tile.animations[frame].first);
			  tile.src.y = static_cast<float>(tile.animations[frame].second);
		  }
	  }
	);
}

auto TileMap::Render( ) -> void
{
	const auto& eachLayer = maps[currentLevelSelected];
	ranges::for_each(
	  eachLayer,
	  [&](const auto& mapFiles)
	  {
		  // const std::string& nameLayer = mapFiles.first;
		  // const std::vector<Tile>& tiles = mapFiles.second;
		  // Logger::Debug(LogType::Log, "TileMap::Render: ", nameLayer);
		  for (const auto& tile : mapFiles.second)
		  {
			  // tile.Render(*m_textureManager);
			  SDL_Rect rect_dst	  //
				{				  //
				  static_cast<int>(tile.dst.x) * static_cast<int>(tile.scale.x),
				  static_cast<int>(tile.dst.y) * static_cast<int>(tile.scale.y),
				  static_cast<int>(tile.size.x) * static_cast<int>(tile.scale.x),
				  static_cast<int>(tile.size.y) * static_cast<int>(tile.scale.y)
				};

			  SDL_Rect rect_src	  //
				{				  //
				  static_cast<int>(tile.src.x),
				  static_cast<int>(tile.src.y),
				  static_cast<int>(tile.size.x),
				  static_cast<int>(tile.size.y)
				};

			  m_textureManager->Render(rect_src, rect_dst, tile.name);
		  }
	  }
	);
}
*/