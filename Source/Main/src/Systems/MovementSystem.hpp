#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Utils/EnumComponentID.hpp"
#include "../Input/Controller.h"
#include <ranges>

class MovementSystem : public System {
private:
public:
  MovementSystem( ) {
	RequireComponent<TransformComponent>( );
	RequireComponent<RigidBodyComponent>( );
  }
  // virtual ~MovementSystem( ) = default;	// Virtual is Expensive

  auto Update(const float& deltaTime) -> void {
	auto eachEntity = [&](const Entity& entity) -> void {
	  TransformComponent& transform = entity.GetComponent<TransformComponent>( );
	  RigidBodyComponent& rigidbody = entity.template GetComponent<RigidBodyComponent>( );

	  float movepl = 5.0f;

	  if (Controller::Instance( ).MoveLeft( )) {
		// transform.position.TransformX(-movepl);
		rigidbody.ApplyForceX(-movepl);
		// Logger::Debug(LogType::Check, "MovementSystem::Update, move left.",
		// transform.position.x);
	  } else if (Controller::Instance( ).MoveRight( )) {
		// transform.position.TransformX(movepl);
		rigidbody.ApplyForceX(movepl);
		// Logger::Debug(LogType::Check, "MovementSystem::Update, move right.",
		// transform.position.x);
	  } else {
		rigidbody.UnsetForce( );
	  }

	  // OLD
	  //  if (Controller::Instance( )->MoveLeft( )) {
	  // // transform.position.TransformX(-movepl);
	  // rigidbody.ApplyForceX(-movepl);
	  // // Logger::Debug(LogType::Check, "MovementSystem::Update, move left.",
	  // // transform.position.x);
	  //  } else if (Controller::Instance( )->MoveRight( )) {
	  // // transform.position.TransformX(movepl);
	  // rigidbody.ApplyForceX(movepl);
	  // // Logger::Debug(LogType::Check, "MovementSystem::Update, move right.",
	  // // transform.position.x);
	  //  } else {
	  // rigidbody.UnsetForce( );
	  //  }

	  rigidbody.Update(deltaTime);

	  transform.position.TransformX(rigidbody.Position( ).x);
	  transform.position.TransformY(rigidbody.Position( ).y);
	  // transform.position.TransformX(rigidbody.Velocity( ).x);
	  // transform.position.TransformY(rigidbody.Velocity( ).y);

	  //  Logger::Debug(
	  // LogType::Debug,
	  // "MovementSystem::Update ",
	  // "X:",
	  // transform.position.x,
	  // " - Y: ",
	  // transform.position.y
	  //  );
	};

	std::ranges::for_each(GetEntities( ), eachEntity);
	//

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

		 // const Uint8* keyState = SDL_GetKeyboardState(NULL);

//  switch (m_event.type) {
// case SDL_KEYDOWN:
//
//   if (m_event.key.keysym.sym == SDLK_a || m_event.key.keysym.sym == SDLK_LEFT) {
// 	transform.position.TransformX(-movepl);
// 	Logger::Debug(
// 	  LogType::Check,
// 	  "MovementSystem::Update, move left.",
// 	  transform.position.x
// 	);
//   } else if (m_event.key.keysym.sym == SDLK_d || m_event.key.keysym.sym == SDLK_RIGHT) {
// 	transform.position.TransformX(movepl);
// 	Logger::Debug(
// 	  LogType::Check,
// 	  "MovementSystem::Update, move right.",
// 	  transform.position.x
// 	);
//   }
//   break;
// default: break;
//  }
//
//  if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
// transform.position.TransformX(-movepl);
// Logger::Debug(LogType::Check, "MovementSystem::Update, move left.", transform.position.x);
//  } else if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
// transform.position.TransformX(movepl);
// Logger::Debug(LogType::Check, "MovementSystem::Update, move right.", transform.position.x);
//  }

//  Logger::Debug(
// LogType::Check,
// "MovementSystem::Update, move left.",
// Controller::Instance( )->MoveLeft( )
//  );