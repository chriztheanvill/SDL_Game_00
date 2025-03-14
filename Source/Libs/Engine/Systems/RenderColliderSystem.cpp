//
// Created by cris on 2/15/25.
//

#include "RenderColliderSystem.hpp"

#include "../Components/GraphicComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.hpp"
#include "../Core/Time.h"
#include "Components/ColliderComponent.hpp"

RenderColliderSystem::RenderColliderSystem(SDL_Renderer* render)
    : m_render(render) {
  RequireComponent<TransformComponent>();
  RequireComponent<ColliderComponent>();
}

void DrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
  int x = 0;
  int y = radius;
  int d = 3 - 2 * radius;

  auto DrawSymmetricPoints = [&](int x, int y) {
    SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
    SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
    SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
    SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
    SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
    SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
  };

  while (y >= x) {
    DrawSymmetricPoints(x, y);
    x++;
    if (d > 0) {
      y--;
      d += 4 * (x - y) + 10;
    } else {
      d += 4 * x + 6;
    }
  }
}

auto RenderColliderSystem::Render() -> void {
  for (auto& entity:
       GetEntities() | std::views::transform([](auto& ptr) -> Entity& { return ptr; })) {
    const auto& transform = entity.GetComponent<TransformComponent>();
    const auto& collider = entity.GetComponent<ColliderComponent>();

    // const ColliderComponent::Shape* shape = std::get_if<ColliderComponent::Box>(&collider.shape);
    // if (!shape) { shape = std::get_if<ColliderComponent::Circle>(&collider.shape); }
    // // auto* circle = std::get_if<ColliderComponent::Circle>(&collider.shape);

    SDL_Color color = {};
    if (collider.isTrigger) {
      color = SDL_Color { 255, 20, 20, 255 };
    } else {
      color = SDL_Color { 255, 255, 255, 255 };
      // color = SDL_Color { 0, 128, 255, 255 }; // Azul
    }

    auto* box = std::get_if<ColliderComponent::Box>(&collider.shape);
    auto* circle = std::get_if<ColliderComponent::Circle>(&collider.shape);

    SDL_SetRenderDrawColor(m_render, color.r, color.g, color.b, color.a);
    if (box) {
      // Logger::Debug(LogType::Check, "RenderColliderSystem::Render box ");
      SDL_Rect rect { static_cast<int>(transform.position.x + box->offset.x),
                      static_cast<int>(transform.position.y + box->offset.y),
                      static_cast<int>(box->size.x * transform.scale.x),
                      static_cast<int>(box->size.y * transform.scale.x) };

      SDL_RenderDrawRect(m_render, &rect);
    } else {
      // Logger::Debug(LogType::Check, "RenderColliderSystem::Render circle ");
      // Logger::Debug(LogType::Debug, "x: ", transform.position.x);
      // Logger::Debug(LogType::Debug, "y: ", transform.position.y);

      int radius = static_cast<int>(circle->radius * transform.scale.x / 2);
      int x = static_cast<int>(transform.position.x + circle->offset.x + radius);
      int y = static_cast<int>(transform.position.y + circle->offset.y + radius);

      // Logger::Debug(LogType::Debug, "- x: ", x);
      // Logger::Debug(LogType::Debug, "- y: ", y);

      DrawCircle(m_render, x, y, radius);
      //
    }

  } // FOR
}