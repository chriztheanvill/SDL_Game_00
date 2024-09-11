//
// Created by cris on 8/13/24.
//

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <bitset>
#include <cstdint>
#include <memory>
#include <vector>

#include "GenID.hpp"

class Entity;

class System {
 private:
  Signature m_componentSignature;
  std::vector<Entity> m_entities;

 public:
  System() = default;
  ~System() = default;

  void AddEntity(const Entity& entity);
  void RemoveEntity(const Entity& entity);
  [[nodiscard]] auto GetEntities() -> std::vector<Entity>&;
  [[nodiscard]] auto GetSignature() const -> const Signature&;

  template<class T> void RequireComponent() {
    const uint16_t componentID = GenID<T>::ID();
    m_componentSignature.set(componentID);
  }
};

#endif // SYSTEM_HPP
