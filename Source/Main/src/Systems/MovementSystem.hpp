#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include "../ECS/Registry.hpp"

#include <ranges>

class MovementSystem : public System {
 private:
  // float movementSpeed = 50.0f; // Old
  float m_movementSpeed = 150.0f;
  // float movementSpeed = 0.05f * 1000; // Sin sync
  // float movementSpeed = 0.02f; // Sin sync

 public:
  MovementSystem();

  auto Update(float deltaTime) -> void;
};

#endif // MOVEMENT_SYSTEM_HPP

       /*
         auto eachEntity = [&](const Entity& entity) -> void {
               TransformComponent& transform = entity.GetComponent<TransformComponent>();
               RigidBodyComponent& rigidbody = entity.template GetComponent<RigidBodyComponent>();
       
               rigidbody.ApplyForceX(
                 static_cast<float>(Controller::Instance().MoveRight() -
         Controller::Instance().MoveLeft())
                 * movementSpeed
               );
       
               // rigidbody.ApplyForceY(100);
       
               rigidbody.Update(deltaTime);
       
               // Logger::Debug(LogType::Log, "MovementSystem::Update tr pos x: ", transform.position.x);
               // Logger::Debug(LogType::Log, "MovementSystem::Update r ", rigidbody.Position().x);
               Logger::Debug(LogType::Log, "MovementSystem::Update tr pos x: ", transform.position.y);
               Logger::Debug(LogType::Log, "MovementSystem::Update r x ", rigidbody.Position().y);
               Logger::Debug(LogType::Log, "MovementSystem::Update r y ", rigidbody.Velocity().y);
       
               transform.position.TransformX(rigidbody.Velocity().x);
               transform.position.TransformY(rigidbody.Velocity().y);
             };
       
             std::ranges::for_each(GetEntities(), eachEntity);
        */

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

// if (Controller::Instance().MoveLeft()) {
//   // transform.position.TransformX(-movepl);
//   rigidbody.ApplyForceX(-movepl);
//   // Logger::Debug(LogType::Check, "MovementSystem::Update, move left.",
//   // transform.position.x);
// } else if (Controller::Instance().MoveRight()) {
//   // transform.position.TransformX(movepl);
//   rigidbody.ApplyForceX(movepl);
//   // Logger::Debug(LogType::Check, "MovementSystem::Update, move right.",
//   // transform.position.x);
// } else {
//   rigidbody.UnsetForce();
// }

//  Logger::Debug(
// LogType::Debug,
// "MovementSystem::Update ",
// "X:",
// transform.position.x,
// " - Y: ",
// transform.position.y
//  );