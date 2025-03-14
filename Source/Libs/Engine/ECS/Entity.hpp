//
// Created by cris on 8/13/24.
//

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <expected> // https://en.cppreference.com/w/cpp/utility/expected
#include <functional>
#include <map>
#include <memory>
#include <ranges>
#include <set>
#include <typeindex>
#include <vector>

class Entity {
 private:
  uint64_t m_id;

  std::string m_name;

 public:
  Entity(uint64_t id = 0, std::string name = "Empty_Entity");
  // Entity(const Entity& entity) = default;	  // Llama al operador ==
  [[nodiscard]] auto GetID() const -> uint64_t;
  auto ReassignID(uint64_t) -> void;

  auto operator<=>(const Entity& other) const = default;

  constexpr auto GetName() const -> std::string { return m_name; }

  bool m_enabled = true;

  // // Registry Part

  class Registry* m_registry;

  template<typename T, typename... Ts> auto AddComponent(Ts&&... args) -> void;
  template<typename T> auto RemoveComponent() -> void;
  template<typename T> auto DisableComponent() -> void;
  template<typename T> [[nodiscard]] auto HasComponent() const -> bool;
  // template<typename T> auto GetComponent() -> std::reference_wrapper<T>;
  template<typename T> auto GetComponent() const -> T&;
};

/*
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||| -- Body -- ||||||||||||||||||||||||||||||||||||||
 */

#include "Registry.hpp"

template<typename T, typename... Ts> auto Entity::AddComponent(Ts&&... args) -> void {
  m_registry->AddComponent<T>(*this, std::forward<Ts>(args)...);
}

template<typename T> auto Entity::RemoveComponent() -> void {
  m_registry->RemoveComponent<T>(*this);
}

template<typename T> auto Entity::DisableComponent() -> void {
  m_registry->DisableComponent<T>(*this);
}

template<typename T> auto Entity::HasComponent() const -> bool {
  return m_registry->HasComponent<T>(*this);
}

// template<typename T> auto Entity::GetComponent() -> std::reference_wrapper<T> {
template<typename T> auto Entity::GetComponent() const -> T& {
  return m_registry->GetComponent<T>(*this);
}

#endif // ENTITY_HPP

       // Se puede usar, que regrese bool pero solo en ciertas ocaciones
// auto operator<=>(const Entity& other) const -> bool = default;

// auto operator=(const Entity& other) -> Entity& = default;
// auto operator==(const Entity& other) const -> bool = default;
// auto operator=(Entity&& other) -> Entity& = default;
// auto operator==(const Entity& other) const -> bool {
// 	return (m_id == other.m_id);
// }
// auto operator!=(const Entity& other) const -> bool {
// 	return !(m_id == other.m_id);
// }
// auto operator>(const Entity& other) const -> bool {
// 	return (m_id > other.m_id);
// }
// auto operator<(const Entity& other) const -> bool {
// 	return (m_id < other.m_id);
// }
// REGION: ################################################ Operators