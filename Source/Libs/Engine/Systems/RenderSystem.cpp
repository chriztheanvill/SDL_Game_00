//
// Created by cris on 9/6/24.
//

#include "RenderSystem.hpp"

#include "../Components/GraphicComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.hpp"
#include "../Core/Time.h"

// std::function<void(void)> RenderSystem::sf_Sort = nullptr;

RenderSystem::RenderSystem(std::shared_ptr<TextureManager>& textureManager)
    : m_textureManager(textureManager) {
  m_render = m_textureManager->GetRender();
  RequireComponent<TransformComponent>();
  RequireComponent<GraphicComponent>();

  // sf_Sort = std::bind(&RenderSystem::Sort, this);
}

auto RenderSystem::Sort() -> void {
  assert(!GetEntities().empty() || !fprintf(stderr, "RenderSystem::Sort() No entities: \n"));

  // Mas Pesado que partition.
  std::ranges::sort(
    GetEntities() | std::ranges::views::take_while([](Entity& entity) {
    return entity.GetComponent<GraphicComponent>().YSort;
  }),
    [](Entity& lhs, Entity& rhs) {
    const TransformComponent& lt = lhs.GetComponent<TransformComponent>();
    const TransformComponent& rt = rhs.GetComponent<TransformComponent>();

    return lt.position.y > rt.position.y;
  }
  );

  std::ranges::sort(GetEntities(), [](Entity& lhs, Entity& rhs) {
    return lhs.GetComponent<GraphicComponent>().zIndex
           < rhs.GetComponent<GraphicComponent>().zIndex;
  });
}

auto RenderSystem::Render() -> void {
  for (auto& entity: GetEntities()) {
    auto& transform = entity.GetComponent<TransformComponent>();
    auto& graphic = entity.GetComponent<GraphicComponent>();
    // const GraphicComponent& graphic = entity.get().template GetComponent<GraphicComponent>();

    // SDL_Rect src = graphic.src;
    SDL_Rect dst {};

    if (std::holds_alternative<GraphicComponent::Tile>(graphic.type)) {
      // if (auto* val = std::get_if<GraphicComponent::Tile>(&graphic.type)) {
      //
      //      Tilemap || タイルマップ  (Tairu mappu)
      //
      // Logger::Debug(LogType::Debug, "RenderSystem::Render tile ");

      dst = { static_cast<int>(transform.position.x * transform.scale.x),
              static_cast<int>(transform.position.y * transform.scale.y),
              static_cast<int>(graphic.src.w * transform.scale.x),
              static_cast<int>(graphic.src.h * transform.scale.y) };

    } else if (std::holds_alternative<GraphicComponent::Sprite>(graphic.type)) {
      //
      //      sprite || スプライト (Supuraito)
      //
      // Logger::Debug(LogType::Check, "RenderSystem::Render sprite ");

      dst = { static_cast<int>(transform.position.x),
              static_cast<int>(transform.position.y),
              static_cast<int>(graphic.src.w * transform.scale.x),
              static_cast<int>(graphic.src.h * transform.scale.y) };

      // SDL_Rect coll { dst.x - 5, dst.y - 5, dst.w + 10, dst.h + 10 };
      // //
      // SDL_SetRenderDrawColor(m_render, 255, 255, 255, 255);
      // SDL_RenderFillRect(m_render, &coll);

      // #ifdef NDEBUG
      // #else
      //       auto color = SDL_Color { 255, 255, 255, 255 };
      //       SDL_SetRenderDrawColor(m_render, color.r, color.g, color.b, color.a);
      //       SDL_RenderFillRect(m_render, &dst);
      //
      // #endif
    }

    SDL_RenderCopyEx(
      m_render,
      m_textureManager->GetTexture(graphic.assetName),
      &graphic.src,
      &dst,
      transform.rotation,
      nullptr,
      SDL_FLIP_NONE
    );

    // Logger::Debug(LogType::Debug, "RenderSystem::Render pos x: ", transform.position.x);
    // Logger::Debug(LogType::Debug, "RenderSystem::Render sca x: ", transform.scale.x);
    // Logger::Debug(LogType::Debug, "RenderSystem::Render src w: ", sprite.src.w);
  } // For
}

/*
 * SORT
 // auto partition = std::ranges::partition(GetEntities(), [](const Entity& rhs) {
  //   return rhs.GetComponent<GraphicComponent>().YSort;
  // });

  // OK a medias, siempre va a ordenar
  // por como se agrego al sistema, no por posision
  // std::ranges::sort(
  //   GetEntities().begin(),
  //   std::ranges::partition(
  //     GetEntities(), [](const Entity& rhs) { return rhs.GetComponent<GraphicComponent>().YSort; }
  //   ).begin()
  // );

  // Es mas ligero
  // Si es positivo es <
  // Si es negativo es >
  // std::ranges::sort(GetEntities() | std::ranges::views::drop_while([](const Entity& entity) {
  //   return entity.GetComponent<GraphicComponent>().YSort;
  // }));

  // Mas Pesado que partition.
  std::ranges::sort(
    GetEntities() | std::ranges::views::take_while([](const Entity& entity) {
    return entity.GetComponent<GraphicComponent>().YSort;
  }),
    [](const Entity& lhs, const Entity& rhs) {
    const TransformComponent& lt = lhs.GetComponent<TransformComponent>();
    const TransformComponent& rt = rhs.GetComponent<TransformComponent>();

    return lt.position.y > rt.position.y;
  }
  );

  std::ranges::sort(GetEntities(), [](const Entity& lhs, const Entity& rhs) {
    // auto lgraph = lhs.GetComponent<GraphicComponent>();
    // auto rgraph = rhs.GetComponent<GraphicComponent>();

    // if (lgraph.YSort && rgraph.YSort) {
    //   Logger::Debug(LogType::Debug, "++++ Sort entities lhs: ", lhs.GetName(), " - ",
    //   lgraph.YSort); Logger::Debug(LogType::Debug, "++++ Sort entities rhs: ", rhs.GetName(), " -
    //   ", rgraph.YSort);
    // }

    // int16_t li = lgraph.zIndex;
    // int16_t ri = rgraph.zIndex;
    //
    // const TransformComponent& lt = lhs.GetComponent<TransformComponent>();
    // const TransformComponent& rt = rhs.GetComponent<TransformComponent>();

    // if (li == ri) {
    //   return lhs.GetComponent<TransformComponent>().position.y
    //          < rhs.GetComponent<TransformComponent>().position.y;
    // }

    // if (lgraph.YSort && rgraph.YSort) {
    //   return lhs.GetComponent<TransformComponent>().position.y
    //          < rhs.GetComponent<TransformComponent>().position.y;
    // }

    // if (lgraph.YSort && rgraph.YSort) { // Solo si tienen YSort
    //   const TransformComponent& lt = lhs.GetComponent<TransformComponent>();
    //   const TransformComponent& rt = rhs.GetComponent<TransformComponent>();
    //
    //   if (li == ri) return lt.position.y < rt.position.y;
    // }

    return lhs.GetComponent<GraphicComponent>().zIndex
           < rhs.GetComponent<GraphicComponent>().zIndex;
    // return li < ri;
  });
 */

// =============================================================================
// =============================================================================

// Original
// Logger::Debug(LogType::Check, "RenderSystem::Render SpriteAnimated ");
// dst = { static_cast<int>(transform.position.x),
//         static_cast<int>(transform.position.y),
//         static_cast<int>(graphic.src.w * transform.scale.x),
//         static_cast<int>(graphic.src.h * transform.scale.y) };
//
// SDL_Rect coll { dst.x - 5, dst.y - 5, dst.w + 10, dst.h + 10 };
//
// SDL_SetRenderDrawColor(m_render, 255, 255, 255, 255);
// SDL_RenderFillRect(m_render, &coll);
// uint16_t speed = (SDL_GetTicks64() / 100) % tanim->framesAmount;

// OK
// std::sort(GetEntities().begin(), GetEntities().end(), [](Entity a, Entity b) {
//   auto agraph = a.GetComponent<GraphicComponent>().zIndex;
//   auto bgraph = b.GetComponent<GraphicComponent>().zIndex;
//   return agraph < bgraph;
// });

// OK
// if (tanim->currentTime - tanim->lastFrameTime
//     >= tanim->frames.at(tanim->currentFrame).duration) {
//   // Logger::Debug(LogType::Debug, "RenderSystem::Render tileAnimated dentro ++++ ");
//   tanim->lastFrameTime = tanim->currentTime;
//   tanim->currentFrame = (tanim->currentFrame + 1) % tanim->frames.size();
// }

// auto GetAnimations(GraphicComponent::RenderType* type, float deltaTime) -> void {
//   GraphicComponent::RenderAnimatedType* rtype;
//   if (auto atile = dynamic_cast<GraphicComponent::TileAnimated*>(type); atile) {
//     rtype = atile;
//   } else if (auto asprite = dynamic_cast<GraphicComponent::SpriteAnimated*>(type); asprite) {
//     rtype = asprite;
//   }
//
//   rtype->currentTime += (deltaTime * 1000);
//
//   if (rtype->currentTime - rtype->lastFrameTime >=
//   rtype->frames.at(rtype->currentFrame).duration) {
//     rtype->lastFrameTime = rtype->currentTime;
//     rtype->currentFrame = (rtype->currentFrame + 1) % rtype->frames.size();
//   }
// }