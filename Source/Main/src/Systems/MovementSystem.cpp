//
// Created by cris on 9/6/24.
//
#include "MovementSystem.hpp"

#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.hpp"
#include "../Input/Controller.h"

MovementSystem::MovementSystem() {
  RequireComponent<TransformComponent>();
  RequireComponent<RigidBodyComponent>();
}

auto MovementSystem::Update(float deltaTime) -> void {
  // auto eachEntity = [&](const Entity& entity) -> void {   };
  // std::ranges::for_each(GetEntities(), eachEntity);

  for (const Entity& entity: GetEntities()) {
    TransformComponent& transform = entity.GetComponent<TransformComponent>();
    RigidBodyComponent& rigidbody = entity.template GetComponent<RigidBodyComponent>();

    // rigidbody.ApplyForceX(
    //   static_cast<float>(Controller::Instance().MoveRight() - Controller::Instance().MoveLeft())
    //   * m_movementSpeed
    // );
    //
    // rigidbody.ApplyForceY(
    //   static_cast<float>(Controller::Instance().MoveDown() - Controller::Instance().MoveUp())
    //   * m_movementSpeed
    // );

    rigidbody.Update(deltaTime);

    // rigidbody.ApplyForceY(100);

    transform.position.TransformX(rigidbody.Velocity().x);
    transform.position.TransformY(rigidbody.Velocity().y);
  }
}