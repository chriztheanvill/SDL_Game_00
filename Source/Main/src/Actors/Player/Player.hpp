//
// Created by cris on 2/24/25.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../../Game/IGameObject.hpp"

#include <Components/AnimationComponent.hpp>
#include <Components/ColliderComponent.hpp>
#include <Components/RigidBodyComponent.h>
#include <Components/TransformComponent.hpp>
#include <ECS/Registry.hpp>
#include <Graphics/TextureManager.h>
#include <Input/Controller.h>
#include <Parsers/MapFileParser.hpp>
#include <Utils/Logger.h>
#include <Utils/Utils.hpp>

class Player : public IGameObject {
  Entity m_entity;

 public:
  Player(std::shared_ptr<Registry>&);
  virtual ~Player() override;

  auto Init() -> void override;
  auto Update(float) -> void override;

  std::shared_ptr<Registry> m_registry;

 protected:
 private:
};

#endif // PLAYER_HPP