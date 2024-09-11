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

auto RenderSystem::Render(float deltaTime) -> void {
  // auto eachEntity = [this](const Entity& entity) -> void {};
  // std::ranges::for_each(GetEntities(), eachEntity);

  Sort();

  // OK
  // std::sort(GetEntities().begin(), GetEntities().end(), [](Entity a, Entity b) {
  //   auto agraph = a.GetComponent<GraphicComponent>().zIndex;
  //   auto bgraph = b.GetComponent<GraphicComponent>().zIndex;
  //   return agraph < bgraph;
  // });

  for (const Entity& entity: GetEntities()) {
    const TransformComponent& transform = entity.GetComponent<TransformComponent>();
    GraphicComponent& graphic = entity.template GetComponent<GraphicComponent>();

    SDL_Rect src {};
    SDL_Rect dst {};

    if (std::holds_alternative<GraphicComponent::Tile>(graphic.type)) {
      // if (auto* val = std::get_if<GraphicComponent::Tile>(&graphic.type)) {
      //
      //      Tilemap || タイルマップ  (Tairu mappu)
      //
      // Logger::Debug(LogType::Debug, "RenderSystem::Render tile ");

      src = graphic.src;

      dst = { static_cast<int>(transform.position.x * transform.scale.x),
              static_cast<int>(transform.position.y * transform.scale.y),
              static_cast<int>(graphic.src.w * transform.scale.x),
              static_cast<int>(graphic.src.h * transform.scale.y) };

    } else if (std::holds_alternative<GraphicComponent::TileAnimated>(graphic.type)) {
      //
      //      Tilemap Animated || タイルマップアニメーション ||  Tairu mappu animēshon
      //
      // Logger::Debug(LogType::Debug, "RenderSystem::Render tileAnimated ");
      //

      auto* tanim = std::get_if<GraphicComponent::TileAnimated>(&graphic.type);

      tanim->currentTime += (deltaTime * 1000);

      if (tanim->currentTime - tanim->lastFrameTime
          >= tanim->frames.at(tanim->currentFrame).duration) {
        // Logger::Debug(LogType::Debug, "RenderSystem::Render tileAnimated dentro ++++ ");
        tanim->lastFrameTime = tanim->currentTime;
        tanim->currentFrame = (tanim->currentFrame + 1) % tanim->frames.size();
      }

      src = { // OK
              tanim->frames[tanim->currentFrame].src.x,
              tanim->frames[tanim->currentFrame].src.y,
              graphic.src.w,
              graphic.src.h
      };

      dst = { static_cast<int>(transform.position.x * transform.scale.x),
              static_cast<int>(transform.position.y * transform.scale.y),
              static_cast<int>(graphic.src.w * transform.scale.x),
              static_cast<int>(graphic.src.h * transform.scale.y) };

    } else if (std::holds_alternative<GraphicComponent::Sprite>(graphic.type)) {
      //
      //      sprite || スプライト (Supuraito)
      //
      // Logger::Debug(LogType::Check, "RenderSystem::Render sprite ");

      src = graphic.src;

      dst = { static_cast<int>(transform.position.x),
              static_cast<int>(transform.position.y),
              static_cast<int>(graphic.src.w * transform.scale.x),
              static_cast<int>(graphic.src.h * transform.scale.y) };

      SDL_Rect coll { dst.x - 5, dst.y - 5, dst.w + 10, dst.h + 10 };

      SDL_SetRenderDrawColor(m_render, 255, 255, 255, 255);
      SDL_RenderFillRect(m_render, &coll);
    } else if (std::holds_alternative<GraphicComponent::SpriteAnimated>(graphic.type)) {
      //
      //      sprite animated || スプライトアニメーション (Supuraito animēshon)
      //
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

      src = graphic.src;
      // uint16_t speed = (SDL_GetTicks64() / 100) % tanim->framesAmount;
      //
      // src = { //
      //         graphic.src.x + (graphic.src.w * tanim->frame),
      //         graphic.src.y,
      //         // graphic.src.y * tanim.row,
      //         graphic.src.w,
      //         graphic.src.h
      // };
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

/*
if (graphic.entityID == 1) {
        Logger::Debug(LogType::Debug, "RenderSystem::Render tileAnimated id: ", tanim->id);
        Logger::Debug(
          LogType::Debug,
          "RenderSystem::Render tileAnimated duration: ",
          tanim->frames.at(tanim->currentFrame).duration
        );
        // Logger::Debug(LogType::Debug, "RenderSystem::Render tileAnimated dt: ", deltaTime);
        Logger::Debug(
          LogType::Debug,
          "RenderSystem::Render tileAnimated tanim->lastFrameTime: ",
          tanim->lastFrameTime
        );
        Logger::Debug(
          LogType::Debug,
          "RenderSystem::Render tileAnimated tanim->currentFrame: ",
          tanim->currentFrame
        );
        Logger::Debug(
          LogType::Debug,
          "RenderSystem::Render tileAnimated tanim->currentTime: ",
          tanim->currentTime
        );
      }
 */