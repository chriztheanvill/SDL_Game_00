#ifndef ECS_HPP
#define ECS_HPP

#include <algorithm>
#include <bitset>
#include <expected>	  // https://en.cppreference.com/w/cpp/utility/expected
#include <functional>
#include <map>
#include <ranges>
#include <set>
#include <typeindex>
#include <vector>

#include "../Utils/Logger.h"
#include "./Pool.hpp"

const unsigned int MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

enum class ParserError
{
	Err,
	Ok
};

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

struct IComponent
{
  protected:
	static int nextID;
};

template <typename T>
class Component : public IComponent
{
	//   public:
	// Component(int id);

	// Regresa un unico ID de Component<T>
	static auto NewId( ) -> int
	{
		static int id = nextID++;
		return id;
	}
};

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

class Entity
{
  public:
	Entity(int id);

	[[nodiscard]] auto GetId( ) const -> int;

	auto operator=(const Entity& other) -> Entity& = default;
	auto operator==(const Entity& other) const -> bool
	{
		return (mID == other.mID);
	}
	auto operator!=(const Entity& other) const -> bool
	{
		return !(mID == other.mID);
	}
	auto operator>(const Entity& other) const -> bool
	{
		return (mID > other.mID);
	}
	auto operator<(const Entity& other) const -> bool
	{
		return (mID < other.mID);
	}

  private:
	int mID;
};

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

class System
{
  public:
	System( ) = default;
	~System( ) = default;

	void AddEntity(Entity entity);
	void RemoveEntity(Entity entity);
	[[nodiscard]] auto GetEntities( ) const -> std::vector<Entity>;
	[[nodiscard]] auto GetSignature( ) const -> const Signature&;

	template <typename TComponent>
	void RequireComponent( );

  private:
	Signature componentSignature;
	std::vector<Entity> entities;
};

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

class Registry
{
  public:
	Registry( ) = default;
	auto NewEntity( ) -> Entity;
	void KillEntity(Entity entity);
	void Update( );

	// Components
	template <typename T, typename... Ts>
	auto AddComponent(Entity entity, Ts&&... args) -> void;

	template <typename T>
	auto RemoveComponent(Entity entity) -> void;

	template <typename T>
	auto HasComponent(Entity entity) const -> bool;

	template <typename T>
	auto GetComponent(Entity entity) const -> T&;

	// Systems
	template <typename T, typename... Ts>
	auto AddSystem(Ts&&... ts) -> void;

	template <typename T>
	auto RemoveSystem( ) -> void;

	template <typename T>
	auto HasSystem( ) const -> bool;

	template <typename T>
	auto GetSystem( ) const -> T&;

	// Manage Systems
	// Checks the component signature of an entity and add the entity to the
	// systems that are interested in it
	void AddEntityToSystem(Entity entity);

  private:
	int numEntities = 0;
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeDeleted;

	template <class T>
	auto FindSystems( ) -> auto;

	// template <class T> // ERROR
	// std::function<T(void)> SomeSome;
	// = [this]( )
	// { return systems.find(static_cast<std::type_index>(typeid(T))); }

	/**
	 * @brief Each pool contains all the data for a certain component type
	 *  {vector index = componetID}, {pool index = entityID}
	 */
	std::vector<IPool*> componentPools;

	/**
	 * @brief
	 * Which components are turned on for an entity
	 */
	std::vector<Signature> entityComponentSignatures;

	/**
	 * @brief Map
	 *
	 */
	std::unordered_map<std::type_index, System*> systems;
};

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

template <class T>
auto Registry::FindSystems( ) -> auto
{
	return systems.find(static_cast<std::type_index>(typeid(T)));
}

// template <typename T>
// auto UMapFindSystems(std::unordered_map<std::type_index, System*>& um) {
// 	return um.find(static_cast<std::type_index>(typeid(T)));
// }

template <typename T, typename... Ts>
auto Registry::AddSystem(Ts&&... ts) -> void
{
	T* newSystem = new T(std::forward<Ts>(ts)...);	 // Update to smart pointer
	systems.insert(static_cast<std::type_index>(typeid(T)), newSystem);
	// systems.insert(std::type_index(typeid(T)), newSystem);

	// systems.insert(typeid(T).name( ), newSystem);
}

template <typename T>
auto Registry::RemoveSystem( ) -> void
{
	auto systemfound = FindSystems<T>(systems);
	// auto systemfound = UMapFindSystems<T>(systems);
	// auto systemfound = systems.find(static_cast<std::type_index>(typeid(T)));
	// auto systemfound = systems.find(std::type_index(typeid(T)));
	systems.erase(systemfound);
	// systems.erase(systems.find(std::type_index(typeid(T))));
}

template <typename T>
auto Registry::HasSystem( ) const -> bool
{
	// return systems.find(static_cast<std::type_index>(typeid(T))) !=
	// 	   systems.end( );

	// WARNING Maybe an error
	return systems.contains(static_cast<std::type_index>(typeid(T)));
}

template <typename T>
auto Registry::GetSystem( ) const -> T&
{
	auto systemfound = FindSystems<T>(systems);
	// auto systemfound = UMapFindSystems<T>(systems);
	// WARNING Maybe an error
	return *(static_cast<T*>(systemfound->second));
	// return *(systemfound->second);
	// auto systemfound = systems.find(static_cast<std::type_index>(typeid(T)));
}

// ----------------------------------------------------------

template <typename T, typename... Ts>
auto Registry::AddComponent(Entity entity, Ts&&... args) -> void
{
	const auto componentID = Component<T>::NewID( );
	const auto entityID = entity.GetId( );

	/**
	 * @brief If the component ID is greatter than the current size of the
	 * 		  componentPools, then resize the vector.
	 */
	if (componentID >= componentPools.size( ))
	{
		componentPools.resize(componentID + 1, nullptr);
	}

	/**
	 * @brief Will pass when is a new ID:
	 *        if we still don't have a pool for that component type
	 */
	if (!componentPools[componentID])
	{
		// TODO(Cris): Checar si se destruye y se crea uno nuevo
		Pool<T>* newComponentPool = new Pool<T>( );
		componentPools[componentID] = newComponentPool;
	}

	/**
	 * @brief Get the pool of the component values for that component type
	 *		  ?? Casting ??
	 */
	// TODO(Cris): Checar si se mueve, o se genera un Reference
	// TODO(Cris): Checar si se puede usar Reference
	Pool<T>* componentPool = Pool<T>(componentPools[componentID]);	 // Cast
	// Pool<T>* componentPool = componentPools[componentID];

	/**
	 * @brief If the entity is greatter than the current size of the component
	 *        tool, then resize the pool
	 *
	 */
	if (entityID >= componentPool->GetSize( ))
	{
		componentPool->Resize(numEntities);
	}

	/**
	 * @brief Create a new Component object of the T, and forward the various
	 *		  parameters to the constructor
	 *
	 */
	T newComponent(std::forward<Ts>(args)...);

	/**
	 * @brief Add the new component to the component pool list, using the entity
	 *		  id as index
	 *
	 */
	componentPool->Set(entityID, newComponent);

	/**
	 * @brief Change the component signature of the entity and set the component
	 *		  id on the bitset to 1
	 *
	 */
	entityComponentSignatures[entityID].set(componentID);
}

template <typename T>
auto Registry::RemoveComponent(Entity entity) -> void
{
	const auto componentID = Component<T>::NewID( );
	const auto entityID = entity.GetId( );

	entityComponentSignatures[entityID].set(componentID, false);
}

template <typename T>
auto Registry::HasComponent(Entity entity) const -> bool
{
	const auto componentID = Component<T>::NewID( );
	const auto entityID = entity.GetId( );

	return entityComponentSignatures[entityID].test(componentID);
}

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

template <class TComponent>
void System::RequireComponent( )
{
	const auto componentID = Component<TComponent>::NewId( );
	componentSignature.set( );
}

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

#endif	 // ECS_HPP