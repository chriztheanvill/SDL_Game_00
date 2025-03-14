//
// Created by cris on 8/13/24.
//

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <expected> // https://en.cppreference.com/w/cpp/utility/expected
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <ranges>
#include <set>
#include <type_traits>
#include <typeindex>
#include <vector>

#include "Pool.hpp"

class Entity;
class System;
#include "GenID.hpp"

class Registry {
 private:
  uint64_t m_numEntities = 0;

  std::set<Entity> m_entitiesToBeAdded;
  std::set<Entity> m_entitiesToBeDeleted;
  // std::vector<Entity> m_entities {};

  template<class T> auto FindSystems() const -> T&;

  /**
   * @brief Each pool contains all the data for a certain component type
   *  {vector index = componetID}, {pool index = entityID}
   */
  std::unordered_map<uint64_t, std::shared_ptr<IPool>> m_componentPools {};
  // std::vector<std::shared_ptr<IPool>> m_componentPools;

  /**
   * @brief
   * Which components are turned on for an entity
   */
  std::unordered_map<uint64_t, Signature> m_entityComponentSignatures {};
  // std::vector<Signature> m_entityComponentSignatures;

  std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems {};

  // Manage Systems
  // Checks the component signature of an entity and add the entity to the
  // systems that are interested in it
  auto AddEntityToSystem(Entity) -> void;
  auto RemoveEntityToSystem(Entity) -> void;

 public:
  Registry() = default;

  auto NewEntity(std::string_view name = "Empty_Entity") -> Entity;
  auto GetEntity(uint64_t val) -> std::expected<std::reference_wrapper<Entity>::type, std::string>;
  void RemoveEntity(Entity& entity);
  // void DisableEntity(Entity& entity);

  auto GetEntitySignatures() -> std::unordered_map<uint64_t, Signature>& {
    return m_entityComponentSignatures;
  }

  auto GetNumEntities() const -> uint64_t { return m_numEntities; }

  void Update();

  // Components

  // template<typename T, typename S> auto AddComponent(const Entity& entity, S) -> void;

  template<typename T, typename... Ts>
  auto AddComponent(const Entity& entity, Ts&&... args) -> void;

  template<typename T> auto RemoveComponent(const Entity& entity) -> void;

  template<typename T> auto DisableComponent(Entity& entity) -> void;

  template<typename T> auto HasComponent(Entity entity) const -> bool;

  template<typename T> auto GetComponent(const Entity& entity) const -> T&;

  // Systems
  template<typename T, typename... Ts> auto AddSystem(Ts&&... ts) -> void;

  template<typename T> auto RemoveSystem() -> void;

  template<typename T> auto HasSystem() const -> bool;

  template<typename T> auto GetSystem() const -> T&;
};

/*
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||| -- Body -- ||||||||||||||||||||||||||||||||||||||
 */

#include "Components/ComponentBase.hpp"
#include "Entity.hpp"
#include "System.hpp"

template<class T> auto Registry::FindSystems() const -> T& {
  // template<class T> auto Registry::FindSystems() const -> std::reference_wrapper<T> {
  const auto it = m_systems.find(static_cast<std::type_index>(typeid(T)));
  assert(it != m_systems.end() && "System not found");

  // return *it->second;
  return *std::static_pointer_cast<T>(it->second);
}

template<typename T, typename... Ts> auto Registry::AddSystem(Ts&&... ts) -> void {
  m_systems.emplace(
    static_cast<std::type_index>(typeid(T)),     // Type
    std::make_shared<T>(std::forward<Ts>(ts)...) // Object
  );
}

template<typename T> auto Registry::RemoveSystem() -> void {
  auto [start, end] { std::ranges::remove(m_systems, FindSystems<T>()) };
  m_systems.erase(start, end);
}

template<typename T> auto Registry::HasSystem() const -> bool {
  return m_systems.contains(static_cast<std::type_index>(typeid(T)));
}

template<typename T> auto Registry::GetSystem() const -> T& { return FindSystems<T>(); }

// template<typename T, typename S> auto Registry::AddComponent(const Entity& entity, S s) -> void {
//   static_assert(std::is_base_of_v<ComponentBase, T>, "T debe derivar de ComponentBase");
//
//   Logger::Debug(LogType::Check, "Registry::AddComponent Simple: ");
//
//   const uint64_t componentID = GenID<T>::ID();
//   const uint64_t entityID = entity.GetID();
//
//   if (!m_componentPools.contains(componentID))
//     m_componentPools.emplace(componentID, std::make_shared<Pool<T>>());
//
//   std::shared_ptr<Pool<T>> componentPool
//     = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));
//
//   // if constexpr (std::is_base_of_v<ComponentBase, T>) {
//   //   Logger::Debug(LogType::Check, "Registry::AddComponent: ");
//   // }
//
//   // Crea componente
//   T component(s.value());
//   componentPool->Add(component);
//
//   Signature signature {};
//
//   if (m_entityComponentSignatures.contains(entityID))
//     signature = m_entityComponentSignatures.at(entityID);
//
//   signature.set(componentID);
//
//   m_entityComponentSignatures.insert_or_assign(entityID, signature);
// }

template<typename T>
constexpr bool is_optional_component_base_v
  = std::is_same_v<std::decay_t<T>, std::optional<ComponentBase>>;

template<typename T, typename... Ts>
auto Registry::AddComponent(const Entity& entity, Ts&&... args) -> void {
  static_assert(std::is_base_of_v<ComponentBase, T>, "T debe derivar de ComponentBase");

  // Logger::Debug(LogType::Check, "Registry::AddComponent Args: ");

  const uint64_t componentID = GenID<T>::ID();
  const uint64_t entityID = entity.GetID();

  if (!m_componentPools.contains(componentID))
    m_componentPools.emplace(componentID, std::make_shared<Pool<T>>());

  std::shared_ptr<Pool<T>> componentPool
    = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));

  // if constexpr (std::is_base_of_v<ComponentBase, T>) {
  //   Logger::Debug(LogType::Check, "Registry::AddComponent: ");
  // }

  // Crea componente
  if constexpr ((is_optional_component_base_v<Ts> || ...)) {
    Logger::Debug(
      LogType::Error,
      "Registry::AddComponent: Al menos un argumento es std::optional<ComponentBase>"
    );
  }
  // else {
  //   std::cout << "Ningún argumento es std::optional<ComponentBase>\n";
  // }

  if constexpr ((std::is_base_of_v<ComponentBase, Ts> && ...)) {
    Logger::Debug(LogType::Check, "Registry::AddComponent: Es un objeto");
    // T component(std::forward<Ts>(args)...);
    // T component(std::forward<Ts>(args)...);
    // componentPool->Add(component);
  } else {
    // Logger::Debug(LogType::Check, "Registry::AddComponent: NOOOOOOOOOOOOOOO Es un objeto");
    T component(entityID, std::forward<Ts>(args)...);
    componentPool->Add(component);
  }

  Signature signature {};

  if (m_entityComponentSignatures.contains(entityID))
    signature = m_entityComponentSignatures.at(entityID);

  signature.set(componentID);

  m_entityComponentSignatures.insert_or_assign(entityID, signature);
}

template<typename T> auto Registry::DisableComponent(Entity& entity) -> void {
  const uint64_t componentID = GenID<T>::ID();
  const uint64_t entityID = entity.GetID();

  using std::ranges::for_each;
  using std::ranges::views::filter;

  for_each(
    m_componentPools
      | filter([componentID](const std::pair<uint64_t, std::shared_ptr<IPool>>& val) {
    return val.first == componentID;
  }),
    [](const auto& val) {
    std::shared_ptr<Pool<T>> tmp = std::static_pointer_cast<Pool<T>>(val.second);
    Logger::Debug(LogType::Warning, "Registry::DisableComponent: ", tmp->Size());
  }
  );
  // if (auto res = std::ranges::find_if(
  // 	  m_componentPools,
  // 	  [componentID](const std::pair<uint64_t, std::shared_ptr<IPool>>& val)
  // {
  // 		  // std::cout << "\n inside: hasit: " << val.first;
  // 		  return val.first == componentID;
  // 	  }
  // 	);
  // 	res != m_componentPools.end( )) {
  // 	std::shared_ptr<Pool<T>> tmp =
  // std::static_pointer_cast<Pool<T>>(res->second);
  // 	Logger::Debug(LogType::Warning, "Registry::DisableComponent: ",
  // tmp->Size( ));
  // }

  // Logger::Debug(
  //   LogType::Check,
  //   "Registry::DisableComponent: ",
  //   m_entityComponentSignatures[entityID]
  // );

  m_entityComponentSignatures[entityID].set(componentID, false);
}

template<typename T> auto Registry::RemoveComponent(const Entity& entity) -> void {
  const uint64_t componentID = GenID<T>::ID();
  const uint64_t entityID = entity.GetID();

  // Jap lecture: ID konpōnento ga mitsukarimasen
  assert(
    m_componentPools.contains(componentID)
    || !fprintf(
      stderr,
      "ID component not found: || IDコンポーネントが見つかりません %s\n",
      entity.GetName().c_str()
    )
  );

  std::shared_ptr<Pool<T>> componentPool
    = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));

  // Usando //  auto Get(const uint64_t& id) -> std::reference_wrapper<T>
  // auto component = componentPool->Get(entityID);
  // componentPool->Remove(component);

  // Usando //  auto Get(const uint64_t& id) -> T&
  // auto* component = &componentPool->Get(entityID); // OK
  // componentPool->Remove(*component);               // OK

  // if (auto componentExpected = componentPool->Get(entityID);
  // componentExpected.has_value( )) {
  // 	componentPool->Remove(componentExpected.value( ));
  // } else {
  // 	Logger::Debug(LogType::Error, componentExpected.error( ));
  // 	return;
  // }

  // std::erase(m_entityComponentSignatures,
  // m_entityComponentSignatures[entityID]);

  if (const auto findSignature = m_entityComponentSignatures.find(entityID);
      findSignature != m_entityComponentSignatures.end())
    m_entityComponentSignatures.erase(findSignature);

  // auto [start, end] {
  // 	// std::ranges::remove_if(m_data, [&](const auto& val) { return
  // val.entityID != id; }) 	std::ranges::remove(m_entityComponentSignatures,
  // m_entityComponentSignatures[entityID])
  // };
  // m_entityComponentSignatures.erase(start, end);
}

template<typename T> auto Registry::HasComponent(Entity entity) const -> bool {
  const uint64_t componentID = GenID<T>::ID();
  const uint64_t entityID = entity.GetID();

  // return m_entityComponentSignatures[entityID].test(componentID);

  return m_entityComponentSignatures.at(entityID).test(componentID);
}

// template<typename T>
// auto Registry::GetComponent(const Entity& entity) const -> std::reference_wrapper<T> {
template<typename T> auto Registry::GetComponent(const Entity& entity) const -> T& {
  const uint64_t componentID = GenID<T>::ID();
  const uint64_t entityID = entity.GetID();

  assert(!entity.GetName().empty() || !fprintf(stderr, "No name in this entity\n"));

  // Jap lecture: ID konpōnento ga mitsukarimasen
  assert(
    m_componentPools.contains(componentID)
    || !fprintf(
      stderr,
      "ID component not found: || IDコンポーネントが見つかりません %s\n",
      entity.GetName().c_str()
    )
  );

  std::shared_ptr<Pool<T>> componentPool
    = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));

  return componentPool->Get(entityID);
}

#endif // REGISTRY_HPP