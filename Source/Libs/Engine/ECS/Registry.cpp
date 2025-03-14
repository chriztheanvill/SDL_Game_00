//
// Created by cris on 8/13/24.
//

#include "Registry.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <ranges>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../Components/AnimationComponent.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../Components/GraphicComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.hpp"

auto Registry::NewEntity(std::string_view name) -> Entity {
  uint16_t entityid = m_numEntities++;

  Signature signature {};
  m_entityComponentSignatures.try_emplace(entityid, signature);

  Entity entity(entityid, std::string(name));
  entity.m_registry = this;

  m_entitiesToBeAdded.emplace(entity);

  return entity;
}

auto Registry::GetEntity(uint64_t id)
  -> std::expected<std::reference_wrapper<Entity>::type, std::string> {
  const Signature& ecsID = m_entityComponentSignatures[id];

  for (auto& eachSystem: m_systems | std::views::values) {
    const Signature& sysSignature = eachSystem->GetSignature();

    bool isInterested = (ecsID & sysSignature) == sysSignature;

    if (isInterested) {
      // Logger::Debug(LogType::Check, "Registry::GetEntity: ", id);
      return eachSystem->GetEntity(id);
    }
  }
  return std::unexpected("Registry::GetEntity Entity not found: \n");
  // assert(false || !fprintf(stderr, "Registry::GetEntity Entity not found:  \n"));
}

void Registry::RemoveEntity(Entity& entity) {
  // auto r = std::ranges::find(m_entities, entity.GetID(), &Entity::GetID);
  // assert(r != m_entities.end() || !fprintf(stderr, "Registry::RemoveEntity Entity not found:
  // \n")); m_entitiesToBeDeleted.emplace(r->GetID());

  const uint16_t entityID = entity.GetID();
  const Signature& ecsID = m_entityComponentSignatures[entityID];

  for (auto& eachSystem: m_systems | std::views::values) {
    const Signature& sysSignature = eachSystem->GetSignature();

    bool isInterested = (ecsID & sysSignature) == sysSignature;

    if (isInterested) {
      Logger::Debug(LogType::Check, "Registry::RemoveEntity: ", entityID);
      eachSystem->RemoveEntity(entityID);
    }
  }
  m_entityComponentSignatures.erase(entityID);

  // auto checkIfComponentExist = [&](const ComponentBase& val) { return val.entityID == entityID;
  // };
  //
  // // Ambos sirven: `auto y typename T`
  // // auto removeComponent = [&](auto& eachPool)
  // auto removeComponent = [&]<typename T>(std::shared_ptr<Pool<T>>& eachPool) {
  //   auto [start, end] { std::ranges::remove_if(eachPool->GetPool(), checkIfComponentExist) };
  //   eachPool->GetPool().erase(start, end);
  // };
  //
  // for (auto& eachPool: m_componentPools | std::views::values) {
  //   if (auto pool = std::dynamic_pointer_cast<Pool<RigidBodyComponent>>(eachPool); pool) {
  //     Logger::Debug(LogType::Check, "Registry::RemoveEntity - RigidBodyComponent: ", entityID);
  //     removeComponent(pool);
  //   } else if (auto pool = std::dynamic_pointer_cast<Pool<TransformComponent>>(eachPool); pool) {
  //     Logger::Debug(LogType::Check, "Registry::RemoveEntity - TransformComponent: ", entityID);
  //     removeComponent(pool);
  //   } else if (auto pool = std::dynamic_pointer_cast<Pool<AnimationComponent>>(eachPool); pool) {
  //     Logger::Debug(LogType::Check, "Registry::RemoveEntity - AnimationComponent: ", entityID);
  //     removeComponent(pool);
  //   } else if (auto pool = std::dynamic_pointer_cast<Pool<ColliderComponent>>(eachPool); pool) {
  //     Logger::Debug(LogType::Check, "Registry::RemoveEntity - ColliderComponent: ", entityID);
  //     removeComponent(pool);
  //   } else if (auto pool = std::dynamic_pointer_cast<Pool<GraphicComponent>>(eachPool); pool) {
  //     Logger::Debug(LogType::Check, "Registry::RemoveEntity - GraphicComponent: ", entityID);
  //     removeComponent(pool);
  //   } else {
  //     Logger::Debug(LogType::Check, "Registry::RemoveEntity - ELSE: ", entityID);
  //   }
  // }

  // ================================

  for (auto& eachPool: m_componentPools | std::views::values) {
    auto removeEntity = [&](auto pool) {
      if (!pool) return;
      auto& poolData = pool->GetPool();
      auto [start, end] = std::ranges::remove_if(poolData, [&](const ComponentBase& val) {
        return val.entityID == entityID;
      });
      poolData.erase(start, end);

      // if (pool) {
      //   auto& poolData = pool->GetPool();
      //   auto [start, end] = std::ranges::remove_if(poolData, [&](const ComponentBase& val) {
      //     return val.entityID == entityID;
      //   });
      //   poolData.erase(start, end);
      // }
    };

    using PoolTypes = std::tuple<
      Pool<RigidBodyComponent>,
      Pool<TransformComponent>,
      Pool<AnimationComponent>,
      Pool<ColliderComponent>,
      Pool<GraphicComponent>>;

    std::apply([&](auto... args) {
      (removeEntity(std::dynamic_pointer_cast<std::decay_t<decltype(args)>>(eachPool)), ...);
    }, PoolTypes {});
  }

  // ==================

  Logger::Debug(LogType::Check, "Registry::RemoveEntity: ", entityID);
}

// void Registry::DisableEntity(Entity& entity) { }

auto Registry::AddEntityToSystem(Entity entity) -> void {
  const uint16_t entityID = entity.GetID();
  const Signature& ecsID = m_entityComponentSignatures[entityID];

  for (auto& eachSystem: m_systems | std::views::values) {
    const Signature& sysSignature = eachSystem->GetSignature();

    bool isInterested = (ecsID & sysSignature) == sysSignature;

    if (isInterested) { eachSystem->AddEntity(entity); }
  }
}

auto Registry::RemoveEntityToSystem(Entity entity) -> void {
  assert(
    !m_entityComponentSignatures.empty()
    || !fprintf(stderr, "Registry::RemoveEntityToSystem No Signatures: \n")
  );

  const uint16_t entityID = entity.GetID();
  const Signature& ecsID = m_entityComponentSignatures[entityID];

  for (auto& eachSystem: m_systems | std::views::values) {
    const Signature& sysSignature = eachSystem->GetSignature();

    bool isInterested = (ecsID & sysSignature) == sysSignature;

    if (isInterested) { eachSystem->RemoveEntity(entityID); }
  }
}

// Se agregan o remueven las entidades, despues de cada frame
void Registry::Update() {
  for (auto& entity: m_entitiesToBeAdded) AddEntityToSystem(entity);
  m_entitiesToBeAdded.clear();

  for (auto& entity: m_entitiesToBeDeleted) { RemoveEntityToSystem(entity); }
  m_entitiesToBeDeleted.clear();
}