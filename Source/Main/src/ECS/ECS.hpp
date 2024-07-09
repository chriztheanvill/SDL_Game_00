#ifndef ECS_HPP
#define ECS_HPP

#include <algorithm>
#include <cstdint>
#include <bitset>
#include <expected>	  // https://en.cppreference.com/w/cpp/utility/expected
#include <functional>
#include <map>
#include <ranges>
#include <algorithm>
#include <set>
#include <typeindex>
#include <vector>
#include <memory>

#include "../Utils/Logger.h"
#include "./Pool.hpp"

constexpr uint16_t MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

// ##########################################################################
// ##########################################################################

struct IComponent {
  protected:
	static uint16_t m_nextID;
};

template <typename T>
class Component : public IComponent {
	// static uint16_t my_id;
  public:
	// Regresa un unico ID de Component<T>
	static auto GetID( ) -> uint16_t {
		// my_id++;
		// my_id: Ese solo se incrementara, cuando existan 2 clases iguales
		// m_nextID: desde IComponent, se incrementa, al agregar cualquier clase
		// Se usa id, para tener la enumeración desde 0, ya que nextID, inicia
		// desde 1
		static uint16_t id = m_nextID++;
		return id;
	}

	// auto operator<=>(const Component<T>&) const = default;
	// auto operator==(const Component<T>& other) const -> bool
	// {
	// 	return this == &other;
	// }
};

// ##########################################################################
// ##########################################################################

class Entity {
  private:
	uint16_t m_id;

	std::string m_name;

  public:
	Entity(uint16_t id, std::string name = "Empty_Entity");
	// Entity(const Entity& entity) = default;	  // Llama al operador ==
	[[nodiscard]] auto GetID( ) const -> uint16_t;

	// REGION: ################################################ Operators

	auto operator<=>(const Entity& other) const = default;
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

	constexpr auto GetName( ) const -> std::string { return m_name; }

	class Registry* m_registry;

	template <typename T, typename... Ts>
	auto AddComponent(Ts&&... args) -> void;

	template <typename T>
	auto RemoveComponent( ) -> void;

	template <typename T>
	auto DisableComponent( ) -> void;

	template <typename T>
	[[nodiscard]] auto HasComponent( ) const -> bool;

	template <typename T>
	auto GetComponent( ) const -> T&;
};

// ##########################################################################
// ##########################################################################

class System {
  private:
	Signature m_componentSignature;
	std::vector<Entity> m_entities;

  public:
	System( ) = default;
	~System( ) = default;

	void AddEntity(const Entity& entity);
	void RemoveEntity(const Entity& entity);
	[[nodiscard]] auto GetEntities( ) const -> std::vector<Entity>;
	[[nodiscard]] auto GetSignature( ) const -> const Signature&;

	template <typename TComponent>
	void RequireComponent( );
};

// ##########################################################################
// ##########################################################################

class Registry {
  private:
	uint16_t m_numEntities = 0;
	std::set<Entity> m_entitiesToBeAdded;
	std::set<Entity> m_entitiesToBeDeleted;

	template <class T>
	auto FindSystems( ) const
	  -> std::expected<
		std::unordered_map<std::type_index, std::shared_ptr<System>>::const_iterator,
		std::string>;
	// auto FindSystems( ) -> std::vector<T>::iterator;

	/**
	 * @brief Each pool contains all the data for a certain component type
	 *  {vector index = componetID}, {pool index = entityID}
	 */
	std::map<uint16_t, std::shared_ptr<IPool>> m_componentPools { };
	// std::vector<std::shared_ptr<IPool>> m_componentPools;

	/**
	 * @brief
	 * Which components are turned on for an entity
	 */
	std::map<uint16_t, Signature> m_entityComponentSignatures { };
	// std::vector<Signature> m_entityComponentSignatures;

	std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems { };

  public:
	Registry( ) = default;
	// Registry(const Registry& other);   // Copy
	auto NewEntity(std::string_view name = "Empty_Entity") -> Entity;
	void KillEntity(Entity entity);
	void UpdateNumEntities(uint16_t val) { m_numEntities += val; }
	void Update( );

	// Components
	template <typename T, typename... Ts>
	auto AddComponent(Entity& entity, Ts&&... args) -> void;

	template <typename T>
	auto RemoveComponent(Entity& entity) -> void;

	template <typename T>
	auto DisableComponent(Entity& entity) -> void;

	template <typename T>
	auto HasComponent(Entity entity) const -> bool;

	template <typename T>
	auto GetComponent(Entity entity) const -> T&;

	// Systems
	template <typename T, typename... Ts>
	auto AddSystem(Ts&&... ts) -> void;

	template <typename T>
	auto RemoveSystem( ) -> bool;

	template <typename T>
	auto HasSystem( ) const -> bool;

	template <typename T>
	auto GetSystem( ) const -> std::shared_ptr<T>;

	// Manage Systems
	// Checks the component signature of an entity and add the entity to the
	// systems that are interested in it
	auto AddEntityToSystem(const Entity& entity) -> void;
};

// ##########################################################################
// ##########################################################################

template <typename T, typename... Ts>
auto Entity::AddComponent(Ts&&... args) -> void {
	m_registry->AddComponent<T>(*this, std::forward<Ts>(args)...);
}

template <typename T>
auto Entity::RemoveComponent( ) -> void {
	m_registry->RemoveComponent<T>(*this);
}

template <typename T>
auto Entity::DisableComponent( ) -> void {
	m_registry->DisableComponent<T>(*this);
}

template <typename T>
auto Entity::HasComponent( ) const -> bool {
	return m_registry->HasComponent<T>(*this);
}

template <typename T>
auto Entity::GetComponent( ) const -> T& {
	return m_registry->GetComponent<T>(*this);
}
// ##########################################################################
// ##########################################################################

template <typename T>
auto Registry::FindSystems( ) const
  -> std::expected<
	std::unordered_map<std::type_index, std::shared_ptr<System>>::const_iterator,
	std::string> {
	auto it = m_systems.find(static_cast<std::type_index>(typeid(T)));
	if (it == m_systems.end( )) return std::unexpected("Registry::FindSystems Cant find in umap");

	// return m_systems.find(std::type_index(typeid(T)));
	return it;
}

template <typename T, typename... Ts>
auto Registry::AddSystem(Ts&&... ts) -> void {
	std::shared_ptr<T> newSystem = std::make_shared<T>(std::forward<Ts>(ts)...);
	m_systems.emplace(static_cast<std::type_index>(typeid(T)), newSystem);

	// m_systems.insert({ static_cast<std::type_index>(typeid(T)), newSystem });
}

template <typename T>
auto Registry::RemoveSystem( ) -> bool {
	std::expected<
	  std::unordered_map<std::type_index, std::shared_ptr<System>>::const_iterator,
	  std::string>
	  systemfound = FindSystems<T>( );

	if (systemfound) {
		m_systems.erase(systemfound.value( ));
		return true;
	}

	Logger::Debug(LogType::Error, "Registry::RemoveSystem: ", systemfound.error( ));

	return false;
	// auto systemfound =
	// m_systems.find(static_cast<std::type_index>(typeid(T))); auto systemfound
	// = systems.find(std::type_index(typeid(T)));
	// systems.erase(systems.find(std::type_index(typeid(T))));
}

template <typename T>
auto Registry::HasSystem( ) const -> bool {
	// return systems.find(static_cast<std::type_index>(typeid(T))) !=
	// 	   systems.end( );

	// WARNING Maybe an error
	return m_systems.contains(static_cast<std::type_index>(typeid(T)));
}

template <typename T>
auto Registry::GetSystem( ) const -> std::shared_ptr<T> {
	std::expected<
	  std::unordered_map<std::type_index, std::shared_ptr<System>>::const_iterator,
	  std::string>
	  systemfound = FindSystems<T>( );

	if (!systemfound) Logger::Debug(LogType::Error, "Registry::GetSystem: ", systemfound.error( ));

	// Logger::Debug(
	//   LogType::Check,
	//   "Registry::GetSystem: Find it v: ",
	//   v.use_count( )
	// );

	// Logger::Debug(
	//   LogType::Check,
	//   "Registry::GetSystem: Find it: ",
	//   systemfound.value( )->second.use_count( )
	// );

	// return *std::static_pointer_cast<T>(systemfound.value( )->second);
	return std::static_pointer_cast<T>(systemfound.value( )->second);
	// auto systemfound = m_systems.find(std::type_index(typeid(T)));
	// auto systemfound = systems.find(static_cast<std::type_index>(typeid(T)));
}

template <typename T, typename... Ts>
auto Registry::AddComponent(Entity& entity, Ts&&... args) -> void {
	/** MARK: AddComponent
	 * Obtener IDs
	 */
	const uint16_t componentID = Component<T>::GetID( );
	const uint16_t entityID = entity.GetID( );

	// std::string tmp = typeid(T).name( );
	// std::string tmp2 = tmp;

	// std::cout << "\n AddComponent: " << tmp2;
	// tmp.erase(std::remove_if(tmp.begin( ), tmp.end( ), ::isdigit), tmp.end( ));
	// std::cout << "\n AddComponent: " << tmp;

	if (!m_componentPools.contains(componentID))
		m_componentPools.emplace(componentID, std::make_shared<Pool<T>>( ));

	std::shared_ptr<Pool<T>> componentPool
	  = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));

	T component(entityID, std::forward<Ts>(args)...);

	componentPool->Add(component);

	Signature signature { };

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

template <typename T>
auto Registry::DisableComponent(Entity& entity) -> void {
	const uint16_t componentID = Component<T>::GetID( );
	const uint16_t entityID = entity.GetID( );

	using std::ranges::for_each;
	using std::ranges::views::filter;

	for_each(
	  m_componentPools
		| filter([componentID](const std::pair<uint16_t, std::shared_ptr<IPool>>& val) {
			  return val.first == componentID;
		  }),
	  [](const auto& val) {
		  std::shared_ptr<Pool<T>> tmp = std::static_pointer_cast<Pool<T>>(val.second);
		  Logger::Debug(LogType::Warning, "Registry::DisableComponent: ", tmp->Size( ));
	  }
	);
	// if (auto res = std::ranges::find_if(
	// 	  m_componentPools,
	// 	  [componentID](const std::pair<uint16_t, std::shared_ptr<IPool>>& val) {
	// 		  // std::cout << "\n inside: hasit: " << val.first;
	// 		  return val.first == componentID;
	// 	  }
	// 	);
	// 	res != m_componentPools.end( )) {
	// 	std::shared_ptr<Pool<T>> tmp = std::static_pointer_cast<Pool<T>>(res->second);
	// 	Logger::Debug(LogType::Warning, "Registry::DisableComponent: ", tmp->Size( ));
	// }

	// Logger::Debug(
	//   LogType::Check,
	//   "Registry::DisableComponent: ",
	//   m_entityComponentSignatures[entityID]
	// );
	m_entityComponentSignatures[entityID].set(componentID, false);
}

template <typename T>
auto Registry::RemoveComponent(Entity& entity) -> void {
	const uint16_t componentID = Component<T>::GetID( );
	const uint16_t entityID = entity.GetID( );

	if (!m_componentPools.contains(componentID)) return;

	std::shared_ptr<Pool<T>> componentPool
	  = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));

	auto* component = &componentPool->Get(entityID);
	componentPool->Remove(*component);

	// if (auto componentExpected = componentPool->Get(entityID); componentExpected.has_value( )) {
	// 	componentPool->Remove(componentExpected.value( ));
	// } else {
	// 	Logger::Debug(LogType::Error, componentExpected.error( ));
	// 	return;
	// }

	// std::erase(m_entityComponentSignatures, m_entityComponentSignatures[entityID]);

	if (const auto findSignature = m_entityComponentSignatures.find(entityID);
		findSignature != m_entityComponentSignatures.end( ))
		m_entityComponentSignatures.erase(findSignature);

	// auto [start, end] {
	// 	// std::ranges::remove_if(m_data, [&](const auto& val) { return val.entityID != id; })
	// 	std::ranges::remove(m_entityComponentSignatures, m_entityComponentSignatures[entityID])
	// };
	// m_entityComponentSignatures.erase(start, end);
}

template <typename T>
auto Registry::HasComponent(Entity entity) const -> bool {
	const uint16_t componentID = Component<T>::GetID( );
	const uint16_t entityID = entity.GetID( );

	// return m_entityComponentSignatures[entityID].test(componentID);

	return m_entityComponentSignatures.at(entityID).test(componentID);
}

template <typename T>
auto Registry::GetComponent(Entity entity) const -> T& {
	const uint16_t componentID = Component<T>::GetID( );
	const uint16_t entityID = entity.GetID( );

	std::shared_ptr<Pool<T>> componentPool
	  = std::static_pointer_cast<Pool<T>>(m_componentPools.at(componentID));

	return componentPool->Get(entityID);
}

// ##########################################################################
// ##########################################################################

template <class T>
void System::RequireComponent( ) {
	const uint16_t componentID = Component<T>::GetID( );
	m_componentSignature.set(componentID);
}

// ##########################################################################
// ##########################################################################

#endif	 // ECS_HPP