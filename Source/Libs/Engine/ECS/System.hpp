//
// Created by cris on 8/13/24.
//

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <bitset>
#include <cstdint>
#include <deque>
#include <memory>
#include <vector>

#include "GenID.hpp"

// #include "./Entity.hpp"
class Entity;

class System {
 private:
  Signature m_componentSignature;
  std::vector<Entity> m_entities;

 public:
  System() = default;
  ~System() = default;

  // auto Hello(uint64_t id) -> uint64_t;

  auto AddEntity(const Entity& entity) -> void;
  auto GetEntity(uint64_t id) -> Entity&;
  // auto RemoveEntity(Entity entity) -> void;
  auto RemoveEntity(uint64_t) -> void;
  // auto RemoveEntity(std::shared_ptr<Entity>& entity) -> void;
  [[nodiscard]] auto GetEntities() -> std::vector<Entity>&;
  [[nodiscard]] auto GetSignature() const -> const Signature&;

  template<class T> auto RequireComponent() -> void {
    const uint64_t componentID = GenID<T>::ID();
    m_componentSignature.set(componentID);
  }
};

#endif // SYSTEM_HPP