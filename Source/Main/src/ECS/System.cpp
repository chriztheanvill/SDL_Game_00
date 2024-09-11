//
// Created by cris on 8/13/24.
//

#include "System.hpp"
#include "./Entity.hpp"

void System::AddEntity(const Entity& entity) { m_entities.push_back(entity); }

void System::RemoveEntity(const Entity& entity) { std::erase(m_entities, entity); }

auto System::GetEntities() -> std::vector<Entity>& { return m_entities; }

auto System::GetSignature() const -> const Signature& { return m_componentSignature; }
