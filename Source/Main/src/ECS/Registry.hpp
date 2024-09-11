//
// Created by cris on 8/13/24.
//

#ifndef REGISTRY_HPP
#define REGISTRY_HPP

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <expected> // https://en.cppreference.com/w/cpp/utility/expected
#include <functional>
#include <map>
#include <memory>
#include <ranges>
#include <set>
#include <typeindex>
#include <vector>

#include "Pool.hpp"

class Entity;
class System;
#include "GenID.hpp"

class Registry {
 private:
  uint16_t m_numEntities = 0;
  std::set<Entity> m_entitiesToBeAdded;
  std::set<Entity> m_entitiesToBeDeleted;

  template<class T> auto FindSystems() const -> T&;
  // template<class T> auto FindSystems() const -> std::reference_wrapper<T>;
  // template<class T> auto FindSystems() const -> std::shared_ptr<System>;

  // template<class T>
  //   auto FindSystems() const
  //     -> std::expected<
  //       std::unordered_map<std::type_index, std::shared_ptr<System>>::const_iterator,
  //       std::string>;

  /**
   * @brief Each pool contains all the data for a certain component type
   *  {vector index = componetID}, {pool index = entityID}
   */
  std::unordered_map<uint16_t, std::shared_ptr<IPool>> m_componentPools {};
  // std::vector<std::shared_ptr<IPool>> m_componentPools;

  /**
   * @brief
   * Which components are turned on for an entity
   */
  std::unordered_map<uint16_t, Signature> m_entityComponentSignatures {};
  // std::vector<Signature> m_entityComponentSignatures;

  std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems {};

 public:
  Registry() = default;
  // Registry(const Registry& other);   // Copy
  auto NewEntity(std::string_view name = "Empty_Entity") -> Entity;
  void KillEntity(Entity entity);

  void UpdateNumEntities(uint16_t val) { m_numEntities += val; }

  void Update();

  // Components
  template<typename T, typename... Ts>
  auto AddComponent(const Entity& entity, Ts&&... args) -> void;

  template<typename T> auto RemoveComponent(const Entity& entity) -> void;

  template<typename T> auto DisableComponent(Entity& entity) -> void;

  template<typename T> auto HasComponent(Entity entity) const -> bool;

  template<typename T> auto GetComponent(const Entity& entity) const -> T&;
  // template<typename T> auto GetComponent(const Entity& entity) const ->
  // std::reference_wrapper<T>;

  // Systems
  template<typename T, typename... Ts> auto AddSystem(Ts&&... ts) -> void;

  template<typename T> auto RemoveSystem() -> void;

  template<typename T> auto HasSystem() const -> bool;

  template<typename T> auto GetSystem() const -> T&;
  // template<typename T> auto GetSystem() const -> std::shared_ptr<T>;
  // template<typename T> auto GetSystem() const -> std::reference_wrapper<T>;

  // Manage Systems
  // Checks the component signature of an entity and add the entity to the
  // systems that are interested in it
  auto AddEntityToSystem(const Entity& entity) -> void;
};

/*
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||||||||||| -- |||||||||||||||||||||||||||||||||||||
 * ||||||||||||||||||||||||||||| -- Body -- ||||||||||||||||||||||||||||||||||||||
 */

#include "Entity.hpp"
#include "System.hpp"

// template<typename T>
// auto Registry::FindSystems() const
//   -> std::unordered_map<std::type_index, std::shared_ptr<System>>::const_iterator {
//   const auto it = m_systems.find(static_cast<std::type_index>(typeid(T)));
//   assert(it != m_systems.end() && "System not found");
//   return it->second;
// }

template<class T> auto Registry::FindSystems() const -> T& {
  // template<class T> auto Registry::FindSystems() const -> std::reference_wrapper<T> {
  const auto it = m_systems.find(static_cast<std::type_index>(typeid(T)));
  assert(it != m_systems.end() && "System not found");

  // return *it->second;
  return *std::static_pointer_cast<T>(it->second);
}

// template<class T> auto Registry::FindSystems() const -> std::shared_ptr<System> {
//   const auto it = m_systems.find(static_cast<std::type_index>(typeid(T)));
//   assert(it != m_systems.end() && "System not found");
//
//   return it->second;
// }

template<typename T, typename... Ts> auto Registry::AddSystem(Ts&&... ts) -> void {
  m_systems.emplace(
    static_cast<std::type_index>(typeid(T)), //
    std::make_shared<T>(std::forward<Ts>(ts)...)
  );
}

template<typename T> auto Registry::RemoveSystem() -> void {
  auto [start, end] { std::ranges::remove(m_systems, FindSystems<T>()) };
  // std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
  m_systems.erase(start, end);

  // m_systems.erase(FindSystems<T>());  // OLD
}

template<typename T> auto Registry::HasSystem() const -> bool {
  return m_systems.contains(static_cast<std::type_index>(typeid(T)));
}

template<typename T> auto Registry::GetSystem() const -> T& { return FindSystems<T>(); }
// template<typename T> auto Registry::GetSystem() const -> std::reference_wrapper<T> {
//   return FindSystems<T>();
//   // return std::static_pointer_cast<T>(FindSystems<T>());
//   // return *std::static_pointer_cast<T>(FindSystems<T>()->second);
// }

// template<typename T> auto Registry::GetSystem() const -> std::shared_ptr<T> {
//   return std::static_pointer_cast<T>(FindSystems<T>()->second);
// }

template<typename T, typename... Ts>
auto Registry::AddComponent(const Entity& entity, Ts&&... args) -> void {
  /** MARK: AddComponent
   * Obtener IDs
   */
  const uint16_t componentID = GenID<T>::ID();
  const uint16_t entityID = entity.GetID();

  // Logger::Debug(LogType::Log, "Registry::AddComponent: type:1 ", typeid(T).name());
  // Logger::Debug(LogType::Log, "Registry::AddComponent: type:2 ", typeid(T).hash_code());

  if (!m_componentPools.contains(componentID))
    m_componentPools.emplace(componentID, std::make_shared<Pool<T>>());

  std::shared_ptr<Pool<T>> componentPool
    = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));

  T component(entityID, std::forward<Ts>(args)...);

  componentPool->Add(component);

  Signature signature {};

  if (m_entityComponentSignatures.contains(entityID))
    signature = m_entityComponentSignatures.at(entityID);

  signature.set(componentID);

  m_entityComponentSignatures.insert_or_assign(entityID, signature);

  // m_entityComponentSignatures[entityID].set(componentID);

  // Logger::Debug(
  //   LogType::Log,
  //   "Registry::AddComponent ID: ",
  //   componentID,
  //   " Se agrego a la entindad id: ",
  //   entityID
  // );
}

template<typename T> auto Registry::DisableComponent(Entity& entity) -> void {
  const uint16_t componentID = GenID<T>::ID();
  const uint16_t entityID = entity.GetID();

  using std::ranges::for_each;
  using std::ranges::views::filter;

  for_each(
    m_componentPools
      | filter([componentID](const std::pair<uint16_t, std::shared_ptr<IPool>>& val) {
    return val.first == componentID;
  }),
    [](const auto& val) {
    std::shared_ptr<Pool<T>> tmp = std::static_pointer_cast<Pool<T>>(val.second);
    Logger::Debug(LogType::Warning, "Registry::DisableComponent: ", tmp->Size());
  }
  );
  // if (auto res = std::ranges::find_if(
  // 	  m_componentPools,
  // 	  [componentID](const std::pair<uint16_t, std::shared_ptr<IPool>>& val)
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
  const uint16_t componentID = GenID<T>::ID();
  const uint16_t entityID = entity.GetID();

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

  // Usando //  auto Get(const uint16_t& id) -> std::reference_wrapper<T>
  // auto component = componentPool->Get(entityID);
  // componentPool->Remove(component);

  // Usando //  auto Get(const uint16_t& id) -> T&
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
  const uint16_t componentID = GenID<T>::ID();
  const uint16_t entityID = entity.GetID();

  // return m_entityComponentSignatures[entityID].test(componentID);

  return m_entityComponentSignatures.at(entityID).test(componentID);
}

// template<typename T>
// auto Registry::GetComponent(const Entity& entity) const -> std::reference_wrapper<T> {
template<typename T> auto Registry::GetComponent(const Entity& entity) const -> T& {
  const uint16_t componentID = GenID<T>::ID();
  const uint16_t entityID = entity.GetID();

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
