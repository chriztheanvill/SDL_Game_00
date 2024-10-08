//
// Created by cris on 9/24/24.
//

#include "CollisionSystem.hpp"

#include "../Components/ColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

CollisionSystem::CollisionSystem() {
  RequireComponent<TransformComponent>();
  RequireComponent<ColliderComponent>();
}

CollisionSystem::~CollisionSystem() { }

auto CollisionSystem::Update(float deltaTime) -> void {
  auto& eachEntity = GetEntities();

  if (eachEntity.size() <= 1) {
    Logger::Debug(LogType::Check, "Collision::Update 1 or 0 colliders ");
    return;
  }

  for (auto i { eachEntity.begin() }; i != eachEntity.end(); ++i) {
    Entity a = *i;

    auto aTransform = a.GetComponent<TransformComponent>();
    auto aCollider = a.GetComponent<ColliderComponent>();

    Logger::Debug(LogType::Log, "Collision::Update a name: ", a.GetName());

    for (auto j = i; j != eachEntity.end(); ++j) {
      Entity b = *j;

      if (a == b) { continue; }

      auto bTransform = b.GetComponent<TransformComponent>();
      auto bCollider = b.GetComponent<ColliderComponent>();

      auto* abox = std::get_if<ColliderComponent::Box>(&aCollider.shape);
      auto* acircle = std::get_if<ColliderComponent::Circle>(&aCollider.shape);

      auto* bbox = std::get_if<ColliderComponent::Box>(&bCollider.shape);
      auto* bcircle = std::get_if<ColliderComponent::Circle>(&bCollider.shape);

      if (bbox) {
        Logger::Debug(LogType::Debug, "Collision::Update bbox ");
        if (abox) {
          Logger::Debug(LogType::Debug, "Collision::Update abox ");
        } else { // aCircle
          Logger::Debug(LogType::Debug, "Collision::Update acircle ");
        }
      } else {   // bCircle
        Logger::Debug(LogType::Debug, "Collision::Update bCircle ");
        if (abox) {
          Logger::Debug(LogType::Debug, "Collision::Update abox ");
        } else { // aCircle
          Logger::Debug(LogType::Debug, "Collision::Update acircle ");
        }
      }

      Logger::Debug(LogType::Debug, "Collision::Update b name: ", b.GetName());
    }
    Logger::Debug(LogType::Debug, "-----------");
  }
}

///
// for (const auto& eachEntity: GetEntities()) {
//   //
//   // Logger::Debug(LogType::Check, "Collision::Update ", eachEntity.GetName());
//   //
// }

// if (auto bbox = std::get_if<ColliderComponent::Box>(&bCollider.shape); bbox) {
//   if (auto abox = std::get_if<ColliderComponent::Box>(&aCollider.shape); abox) {
//   } else if (auto acircle = std::get_if<ColliderComponent::Circle>(&aCollider.shape);
//              acircle) {
//   }
//
//   //
// } else if (auto bcircle = std::get_if<ColliderComponent::Circle>(&bCollider.shape); bcircle) {
//   if (auto abox = std::get_if<ColliderComponent::Box>(&aCollider.shape); abox) {
//   } else if (auto acircle = std::get_if<ColliderComponent::Circle>(&aCollider.shape);
//              acircle) {
//   }
// }