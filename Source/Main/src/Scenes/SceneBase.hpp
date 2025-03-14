//
// Created by cris on 12/28/24.
//

#ifndef SCENEBASE_HPP
#define SCENEBASE_HPP

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

#include <memory>

class IGameObject;

class SceneManager;
class Player;

class SceneBase {
  std::map<SceneSelect, std::string> m_fileNames {
    { SceneSelect::Scene_00, std::string(FileLocations::TileMaps) + "Level_00.json" },
    { SceneSelect::Scene_01, std::string(FileLocations::TileMaps) + "Level_01.json" },
  };

  bool m_btnPress {};
  Entity m_enemy_01;
  // std::unique_ptr<Player> m_player;

  std::optional<TransformComponent> m_transform;
  // TransformComponent m_transform;
  // TransformComponent* m_transform;

 protected:
  auto LoadMap(SceneSelect) -> void;

 public:
  SceneBase();
  virtual ~SceneBase();

  virtual auto Enter() -> void;
  virtual auto Exit() -> void;

  virtual auto Events() -> void;
  virtual auto Update(float deltaTime) -> void;

  // std::shared_ptr<SceneManager> m_sceneManager;
  SceneManager* m_sceneManager;
  // std::vector<std::unique_ptr<class IGameObject>> m_gameObjects;

  std::vector<std::unique_ptr<IGameObject>> m_gameObjects;
  // std::vector<std::reference_wrapper<class IGameObject>> m_gameObjects;
};

#endif // SCENEBASE_HPP