//
// Created by cris on 8/13/24.
//

#include "Entity.hpp"

Entity::Entity(uint64_t id, std::string name)
    : m_id(id)
    , m_name(name) { }

auto Entity::GetID() const -> uint64_t { return m_id; }
auto Entity::ReassignID(uint64_t id) -> void { m_id = id; }