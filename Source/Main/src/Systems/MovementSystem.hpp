#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Utils/EnumComponentID.hpp"

#include <ranges>

class MovementSystem : public System {
  private:
	// bits myBits;

  public:
	MovementSystem( ) {
		// myBits.push_back(ComponentID::Tranform);
		// myBits.push_back(ComponentID::RigidBody);
		RequireComponent<TransformComponent>( );
		RequireComponent<RigidBodyComponent>( );
	}
	// virtual ~MovementSystem( ) = default;	// Virtual is Expensive

	auto Update(const float& deltaTime) -> void {
		auto eachEntity = [&deltaTime](const Entity& entity) -> void {
			TransformComponent& transform = entity.GetComponent<TransformComponent>( );
			RigidBodyComponent& rigidbody = entity.template GetComponent<RigidBodyComponent>( );

			rigidbody.Update(deltaTime);

			transform.position.TransformX(rigidbody.Velocity( ).x);
			transform.position.TransformY(rigidbody.Velocity( ).y);

			// Logger::Debug(
			//   LogType::Debug,
			//   "MovementSystem::Update ",
			//   "X:",
			//   transform.position.x,
			//   " - Y: ",
			//   transform.position.y
			// );
		};

		std::ranges::for_each(GetEntities( ), eachEntity);

		// for (const auto& entity : GetEntities( ))
		// {
		// 	TransformComponent& transform
		// 	  = entity.GetComponent<TransformComponent>( );
		// 	RigidBody& rigidbody = entity.GetComponent<RigidBody>( );

		// 	rigidbody.Update(deltaTime);

		// 	transform.position.TransformX(rigidbody.Velocity( ).x);
		// 	transform.position.TransformY(rigidbody.Velocity( ).y);

		// 	Logger::Debug(
		// 	  LogType::Debug,
		// 	  "MovementSystem::Update ",
		// 	  "X:",
		// 	  transform.position.x,
		// 	  " - Y: ",
		// 	  transform.position.y
		// 	);
		// }
	}
};

#endif	 // MOVEMENTSYSTEM_HPP
