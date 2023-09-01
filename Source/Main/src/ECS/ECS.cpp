#include "ECS.hpp"

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

int IComponent::nextID = 0;	  // Static

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

Entity::Entity(int id)
	: mID(id)
{
}

auto Entity::GetId( ) const -> int { return mID; }

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

auto Registry::NewEntity(std::string_view name) -> Entity
{
	int entityid = numEntities++;
	if (entityid >= entityComponentSignatures.size( ))
	{
		entityComponentSignatures.resize(entityid + 1);
	}
	Entity entity(entityid);
	entitiesToBeAdded.insert(entity);
	Logger::Debug(LogType::Debug,
				  "ECS::Registry::NewEntity: Added a new Entity: ID: ",
				  entityid,
				  "\nName: ",
				  name);

	return entity;
}

auto Registry::AddEntityToSystem(Entity entity) -> void
{
	//
	const int entityID = entity.GetId( );
	const auto& ecsID = entityComponentSignatures[entityID];

	for (auto& system : systems)
	{
		const auto& sysSignature = system.second->GetSignature( );

		// Se hace una comparación por bit
		bool isInterested = (ecsID & sysSignature) == sysSignature;

		if (isInterested) { system.second->AddEntity(entity); }
	}

	// ------------------------
}

void Registry::Update( )
{
	// Agregar
	for (auto entity : entitiesToBeAdded) { AddEntityToSystem(entity); }
	entitiesToBeAdded.clear( );

	// Remover
}

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////

// void System::AddEntity(Entity entity)
// {
// 	auto has_it = [this](Entity entity)
// 	{
// 		return std::find(entities.begin( ), entities.end( ), entity) !=
// 			   entities.end( );
// 	};

// 	auto add_it = [this](const Entity& entity)
// 	{
// 		entities.push_back(entity);
// 		return entity;
// 	};

// 	auto output =
// 		entities | std::views::filter(has_it) | std::views::transform(add_it);

// 	Logger::Debug(LogType::Debug, "ECS::System::AddEntity: ", output);

// 	// auto output = entities |
// 	// 			  std::views::filter([](const int n) { return n % 3 == 0; }) |
// 	// 			  std::views::transform([](const
// }

// void System::RemoveEntity(Entity entity)
// {
// 	auto has_it = [this](Entity entity)
// 	{
// 		return std::find(entities.begin( ), entities.end( ), entity) !=
// 			   entities.end( );
// 	};

// 	auto remove_it = [this](Entity entity)
// 	{
// 		return entities.erase(std::remove_if(entities.begin( ),
// 											 entities.end( ),
// 											 [&entity](Entity other)
// 											 { return entity == other; }),
// 							  entities.end( ));
// 		// return std::erase(entities, entity);
// 	};

// 	auto output = entities | std::views::filter(has_it) |
// 				  std::views::transform(remove_it);

// 	Logger::Debug(LogType::Debug, "ECS::System::RemoveEntity:: ", output);
// }

void System::AddEntity(Entity entity) { entities.push_back(entity); }

void System::RemoveEntity(Entity entity)
{
	entities.erase(std::remove_if(entities.begin( ),
								  entities.end( ),
								  [&entity](Entity other) {
									  return entity.GetId( ) == other.GetId( );
								  }),
				   entities.end( ));
}

auto System::GetEntities( ) const -> std::vector<Entity> { return entities; }

auto System::GetSignature( ) const -> const Signature&
{
	return componentSignature;
}

// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////////////////////