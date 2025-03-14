#include "TileMap.hpp"

#include "../Components/GraphicComponent.hpp"
// #include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.hpp"
#include "../Systems/RenderSystem.hpp"

#include <algorithm>
#include <ranges>

using std::ranges::find_if;
using std::ranges::for_each;
// using std::ranges::remove;
using std::ranges::views::filter;

#include <SDL2/SDL.h>

#include "../Graphics/TextureManager.h"
#include "../Utils/Logger.h"

#include "../Components/TransformComponent.hpp"
#include "../ECS/Registry.hpp"
// #include "../Game/Game.hpp"

namespace views = std::ranges::views;
namespace ranges = std::ranges;

TileMap::TileMap() {
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

TileMap::~TileMap() {
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

auto TileMap::SelectCurrentScenario(SceneSelect levelSelect) -> void {
  currentLevelSelected = levelSelect;
}

auto TileMap::SelectLevel(SceneSelect sceneSelect) -> void {
  Logger::Debug(LogType::Check_01, "TileMap::SelectLevel ", static_cast<int>(sceneSelect));

  assert(
    m_registry->HasSystem<RenderSystem>()
    || !fprintf(stderr, "TileMap::SelectLevel RenderSystem not found: \n")
  );
  // Logger::Debug(LogType::Log, "TileMap::SelectLevel 1 ");

  ClearOtherLevels(sceneSelect);
  AddTileMapToRegistry(sceneSelect);
  AddCollMapToRegistry(sceneSelect);
}

auto TileMap::ClearOtherLevels(SceneSelect sceneSelect) -> void {
  // m_registry->Update();

  // Logger::Debug(LogType::Check, "TileMap::ClearOtherLevels level: ", sceneSelect);
  //
  // for (Entity* entity: m_registry->GetSystem<RenderSystem>().GetEntities()
  //                        | views::filter(
  //                          [&](Entity* entity) -> bool //
  // {                                                    // Filter
  //   GraphicComponent graphic = entity->GetComponent<GraphicComponent>();
  //   auto* tile = std::get_if<GraphicComponent::Tile>(&graphic.type);
  //
  //   // Using shared_ptr
  //   // auto tile = dynamic_cast<GraphicComponent::Tile*>(graphic.type);
  //   // assert(tile || !fprintf(stderr, "Cant load TileMap: %s\n", graphic.assetName.c_str()));
  //
  //   return tile == nullptr //
  //          || tile->level != static_cast<int>(sceneSelect)
  //          || !entity->HasComponent<GraphicComponent>();
  // }
  //                        )) // For
  // {
  //   Logger::Debug(LogType::Log, "TileMap::ClearOtherLevels Entity: ", entity->GetID());
  //   // entity.RemoveComponent<TileComponent>( );
  //   // entity.RemoveComponent<TransformComponent>( );
  //   m_registry->RemoveComponent<GraphicComponent>(*entity);
  //   m_registry->RemoveComponent<TransformComponent>(*entity);
  //   //
  //   m_registry->GetSystem<RenderSystem>().RemoveEntity(*entity);
  //   // m_registry->UpdateNumEntities(-1);
  // }
}

auto TileMap::RemoveLevelFromECS(SceneSelect sceneSelect) -> void {
  // // m_registry->Update();
  //
  // //  Logger::Debug(
  // // LogType::Check,
  // // "TileMap::RemoveLevelFromECS: ",
  // // registry->GetSystem<RenderTileMapSystem>( )->GetEntities( ).size( ) == 0 ?
  // //   " ----------------- Zero" :
  // //   " +++++++++++++++++ Ya tiene algo"
  // //  );
  //
  // for (Entity& entity: m_registry->GetSystem<RenderSystem>().GetEntities()) {
  //   if (!entity.HasComponent<GraphicComponent>()) continue;
  //
  //   GraphicComponent graphic = entity.GetComponent<GraphicComponent>();
  //   auto tile = std::get<GraphicComponent::Tile>(graphic.type);
  //
  //   // Using shared_ptr
  //   // auto tile = dynamic_cast<GraphicComponent::Tile*>(graphic.type);
  //   // assert(tile || !fprintf(stderr, "Cant load TileMap: %s\n", graphic.assetName.c_str()));
  //
  //   if (tile.level != level) continue;
  //   // Logger::Debug(LogType::Log, "TileMap::RemoveLevelFromECS Entity: ", entity.GetID( ));
  //
  //   // auto tmp = entity.GetComponent<TileComponent>( );
  //   // Logger::Debug(LogType::Log, "TileMap------ otherId: ", tmp.entityID);
  //
  //   // entity.RemoveComponent<TileComponent>( );
  //   // entity.RemoveComponent<TransformComponent>( );
  //   //
  //   m_registry->RemoveComponent<GraphicComponent>(entity);
  //   m_registry->RemoveComponent<TransformComponent>(entity);
  //   //
  //   m_registry->GetSystem<RenderSystem>().RemoveEntity(entity);
  //   m_registry->UpdateNumEntities(-1);
  // }
}

auto TileMap::AddCollMapToRegistry(SceneSelect sceneSelect) -> void {
  // Logger::Debug(LogType::Check, "TileMap::AddCollMapToRegistry m_mapColls: ");

  for (const auto& [levelselect, vecs]: m_mapColls) {
    // Logger::Debug(
    //   LogType::Check,
    //   "TileMap::AddCollMapToRegistry level: ",
    //   static_cast<int>(levelselect)
    // );
    if (static_cast<int>(levelselect) != static_cast<int>(sceneSelect)) continue;
    for (const auto& eachVec: vecs) {
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

auto TileMap::AddTileMapToRegistry(SceneSelect sceneSelect) -> void {
  // Logger::Debug(LogType::Check, "TileMap::AddTileMapToRegistry ",
  // static_cast<int>(sceneSelect)); Logger::Debug(LogType::Check, "TileMap::AddTileMapToRegistry
  // ", m_maps.size());

  for (const auto& [levelselect, vecs]: m_maps) {
    // Logger::Debug(
    //   LogType::Log,
    //   "TileMap::SelectLevel levelSelect ",
    //   static_cast<int>(levelselect)
    // );

    if (static_cast<int>(levelselect) != static_cast<int>(sceneSelect)) continue;

    for (const auto& [name, tiles]: vecs) {
      // Logger::Debug(LogType::Log, "TileMap::SelectLevel TileName ", name);
      for (const Tile& eachTile: tiles) {
        // Logger::Debug(LogType::Log, "TileMap::AddTileMapToRegistry eachTile ", eachTile.name);
        // Logger::Debug(LogType::Log, "TileMap::SelectLevel eachTile ", eachTile.order);

        Entity tile
          = m_registry->NewEntity("tile_" + eachTile.name + "_" + std::to_string(eachTile.id));

        Entity* ref = &tile;

        tile.AddComponent<TransformComponent>(
          Vector2D { eachTile.dst.x, eachTile.dst.y },
          Vector2D { static_cast<float>(eachTile.scale), static_cast<float>(eachTile.scale) },
          0
        );

        tile.AddComponent<GraphicComponent>(
          eachTile.name,
          SDL_Rect { static_cast<int>(eachTile.src.x),
                     static_cast<int>(eachTile.src.y),
                     static_cast<int>(eachTile.size.x),
                     static_cast<int>(eachTile.size.y) },
          eachTile.order + std::to_underlying(GraphicComponent::SortLayer::BG),
          false,
          SDL_FLIP_NONE,
          // GraphicComponent::GraphicType::TileAnimated
          GraphicComponent::Tile(eachTile.id, static_cast<int>(sceneSelect))
        );

        if (!eachTile.frames.empty()) {
          // Tiles WITH animations
          // Logger::Debug(LogType::Debug, "TileMap::AddTileMapToRegistry With Animations");

          tile.AddComponent<AnimationComponent>("Default", eachTile.frames);
        }

      } // for each tile
    } // for each map
  } // for maps

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


// tile.AddComponent<TileComponent>(
          //   eachTile.name,
          //   eachTile.id,
          //   level,
          //   0,
          //   SDL_Rect { static_cast<int>(eachTile.src.x),
          //              static_cast<int>(eachTile.src.y),
          //              static_cast<int>(eachTile.size.x),
          //              static_cast<int>(eachTile.size.y) }
          // );
*/