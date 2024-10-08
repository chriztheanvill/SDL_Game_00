//
// Created by cris on 9/6/24.
//

#include "RenderSystem.hpp"

#include "../Components/GraphicComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Core/Time.h"

RenderSystem::RenderSystem(std::shared_ptr<TextureManager>& textureManager)
    : m_textureManager(textureManager)
// RenderSystem(TextureManager* textureManager)
//     : m_textureManager(textureManager)
{
  m_render = m_textureManager->GetRender();
  RequireComponent<TransformComponent>();
  RequireComponent<GraphicComponent>();
}

auto RenderSystem::Sort() -> void {
  std::ranges::sort(GetEntities(), [](const Entity& lhs, const Entity& rhs) {
    auto lgraph = lhs.GetComponent<GraphicComponent>().zIndex;
    auto rgraph = rhs.GetComponent<GraphicComponent>().zIndex;

    return lgraph < rgraph;
  });
}

auto RenderSystem::Render() -> void {
  // auto eachEntity = [this](const Entity& entity) -> void {};
  // std::ranges::for_each(GetEntities(), eachEntity);

  Sort();

  for (const Entity& entity: GetEntities()) {
    const TransformComponent& transform = entity.GetComponent<TransformComponent>();
    GraphicComponent& graphic = entity.template GetComponent<GraphicComponent>();

    SDL_Rect src = graphic.src;
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

    }

    else if (std::holds_alternative<GraphicComponent::Sprite>(graphic.type)) {
      //
      //      sprite || スプライト (Supuraito)
      //
      // Logger::Debug(LogType::Check, "RenderSystem::Render sprite ");

      dst = { static_cast<int>(transform.position.x),
              static_cast<int>(transform.position.y),
              static_cast<int>(graphic.src.w * transform.scale.x),
              static_cast<int>(graphic.src.h * transform.scale.y) };

      // SDL_Rect coll { dst.x - 5, dst.y - 5, dst.w + 10, dst.h + 10 };
      //
      // SDL_SetRenderDrawColor(m_render, 255, 255, 255, 255);
      // SDL_RenderFillRect(m_render, &coll);
    }

    // SDL_SetRenderDrawColor(m_render, 255, 255, 255, 255);
    // SDL_RenderFillRect(m_render, &dst);

    SDL_RenderCopyEx(
      m_render,
      m_textureManager->GetTexture(graphic.assetName),
      &src,
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