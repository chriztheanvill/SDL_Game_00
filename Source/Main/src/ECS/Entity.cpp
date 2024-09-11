//
// Created by cris on 8/13/24.
//

#include "Entity.hpp"

Entity::Entity(uint16_t id, std::string name)
    : m_id(id)
    , m_name(name) { }

auto Entity::GetID() const -> uint16_t { return m_id; }
