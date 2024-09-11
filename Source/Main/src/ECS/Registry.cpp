//
// Created by cris on 8/13/24.
//

#include "Registry.hpp"

auto Registry::NewEntity(std::string_view name) -> Entity {
  uint16_t entityid = m_numEntities++;

  Signature signature;
  m_entityComponentSignatures.try_emplace(entityid, signature);

  Entity entity(entityid, std::string(name));
  entity.m_registry = this;
  m_entitiesToBeAdded.emplace(entity);

  return entity;
}

void Registry::KillEntity(Entity entity) { }

auto Registry::AddEntityToSystem(const Entity& entity) -> void {
  const uint16_t entityID = entity.GetID();
  const std::bitset<32>& ecsID = m_entityComponentSignatures[entityID];

  for (const auto& [f, s]: m_systems) {
    const Signature& sysSignature = s->GetSignature();

    bool isInterested = (ecsID & sysSignature) == sysSignature;

    if (isInterested) { s->AddEntity(entity); }
  }
}

// Se agregan las entidades, despues de cada frame
void Registry::Update() {
  for (const Entity& entity: m_entitiesToBeAdded) AddEntityToSystem(entity);
  m_entitiesToBeAdded.clear();
}
