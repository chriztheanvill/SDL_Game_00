//
// Created by cris on 9/24/24.
//

#include "CollisionSystem.hpp"

#include "../Components/ColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"

#include <ranges>

CollisionSystem::CollisionSystem() {
  RequireComponent<TransformComponent>();
  RequireComponent<ColliderComponent>();
}

CollisionSystem::~CollisionSystem() { }

bool debug = false;

bool AABBCheckBothBoxes(
  float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH
) {
  // if (debug) {
  //   Logger::Debug(LogType::Check, "Collision::AABBCheckBothBoxes ");
  //   Logger::Debug(LogType::Debug, "aX ", aX, " aY ", aY, " aW ", aW, " aH ", aH);
  //   Logger::Debug(LogType::Debug, "bX ", bX, " bY ", bY, " bW ", bW, " bH ", bH);
  // }
  return aX + aW >= bX && //
         bX + bW >= aX && //
         aY + aH >= bY && //
         bY + bH >= aY;
}

bool AABBCheckBothCircles(
  float aRadius, const Vector2D& aPosition, float bRadius, const Vector2D& bPosition
) {
  return aRadius + bRadius >= Vector2D::Distance(aPosition, bPosition);
}

bool AABBCheckBoxCircle(
  const Vector2D& aPosition, const Vector2D& aSize, const Vector2D& bPosition, float bRadius
) {
  // if (debug) {
  //   Logger::Debug(LogType::Check, "Collision::AABBCheckBoxCircle ");
  //   Logger::Debug(LogType::Debug, "aPosition ", aPosition, " aSize ", aSize);
  //   Logger::Debug(LogType::Debug, "bPosition ", bPosition, " bRadius ", bRadius);
  // }

  // Encuentra el punto más cercano dentro de la caja respecto al centro del círculo
  // float closestX = std::max(aPosition.x, std::min(bPosition.x, aPosition.x + aSize.x));
  // float closestY = std::max(aPosition.y, std::min(bPosition.y, aPosition.y + aSize.y));

  float closestX = std::clamp(bPosition.x, aPosition.x - aSize.x / 2, aPosition.x + aSize.x / 2);
  float closestY = std::clamp(bPosition.y, aPosition.y - aSize.y / 2, aPosition.y + aSize.y / 2);

  // Calculamos la distancia desde el centro del círculo al punto más cercano en el rectángulo
  float distancia = Vector2D::Distance(bPosition, Vector2D(closestX, closestY));

  // Verificamos si la distancia es menor o igual al radio del círculo
  return distancia <= bRadius;
}

bool AABBCheck(
  std::variant<ColliderComponent::Box, ColliderComponent::Circle> a,
  std::variant<ColliderComponent::Box, ColliderComponent::Circle> b,
  const TransformComponent& aTransform,
  const TransformComponent& bTransform
) {
  auto* abox = std::get_if<ColliderComponent::Box>(&a);
  auto* acircle = std::get_if<ColliderComponent::Circle>(&a);

  auto* bbox = std::get_if<ColliderComponent::Box>(&b);
  auto* bcircle = std::get_if<ColliderComponent::Circle>(&b);

  if (abox && bbox) {
    return AABBCheckBothBoxes(
      abox->offset.x + aTransform.position.x,
      abox->offset.y + aTransform.position.y,
      abox->size.x * aTransform.scale.x,
      abox->size.y * aTransform.scale.y,
      bbox->offset.x + bTransform.position.x,
      bbox->offset.y + bTransform.position.y,
      bbox->size.x * bTransform.scale.x,
      bbox->size.y * bTransform.scale.y
    );
  } else if (abox && bcircle) {
    return AABBCheckBoxCircle(
      abox->offset + aTransform.position,
      abox->size * aTransform.scale,
      bcircle->offset + bTransform.position,
      bcircle->radius * (bTransform.scale.x / 2)
    );
  } else if (acircle && bbox) {
    return AABBCheckBoxCircle(
      bbox->offset + bTransform.position,
      bbox->size * bTransform.scale,
      acircle->offset + aTransform.position,
      acircle->radius * (aTransform.scale.x / 2)
    );
  } else if (acircle && bcircle) {
    return AABBCheckBothCircles(
      acircle->radius,
      acircle->offset + aTransform.position,
      bcircle->radius,
      bcircle->offset + bTransform.position
    );
  }
  return false;
}

auto CollisionSystem::Update(float deltaTime) -> void {
  std::vector<Entity>& entities = GetEntities();
  if (entities.size() <= 1) return;

  for (auto&& a: entities) {
    auto& aCollider = a.GetComponent<ColliderComponent>();
    auto& aTransform = a.GetComponent<TransformComponent>();

    for (auto&& b: entities | std::views::drop(std::distance(entities.data(), &a) + 1)) {
      if (a == b) continue;

      auto& bCollider = b.GetComponent<ColliderComponent>();
      auto& bTransform = b.GetComponent<TransformComponent>();

      bool check = AABBCheck(aCollider.shape, bCollider.shape, aTransform, bTransform);
      aCollider.isTrigger = bCollider.isTrigger = check;
    }
  }
}

/*
OLD
  const std::vector<std::shared_ptr<Entity>>& eachEntity = GetEntities();

  if (eachEntity.size() <= 1) {
    Logger::Debug(LogType::Check, "Collision::Update 1 or 0 colliders ");
    return;
  }

  for (auto i { eachEntity.begin() }; i != eachEntity.end(); ++i) {
    Entity& a = **i;

    // Get A Components
    const TransformComponent& aTransform = a.GetComponent<TransformComponent>();
    ColliderComponent& aCollider = a.GetComponent<ColliderComponent>();

    // Logger::Debug(LogType::Log, "Collision::Update a name: ", a.GetName());

    if (aCollider.isTrigger) { continue; }

    for (auto j = i; j != eachEntity.end(); ++j) {
      Entity& b = **j;

      if (a == b) { continue; }

      // Get B Components
      const TransformComponent& bTransform = b.GetComponent<TransformComponent>();
      ColliderComponent& bCollider = b.GetComponent<ColliderComponent>();

      if (bCollider.isTrigger) { continue; }

      bool check = AABBCheck(aCollider.shape, bCollider.shape, aTransform, bTransform);

      if (check) {
        aCollider.isTrigger = true;
        bCollider.isTrigger = true;
        Logger::Debug(LogType::Check, "Collision::Update ", a.GetName(), " - ", b.GetName());
      }

      // Logger::Debug(LogType::Debug, "Collision::Update b name: ", b.GetName());

    } // For j

    // Logger::Debug(LogType::Debug, "-----------");

  } // For i
 */