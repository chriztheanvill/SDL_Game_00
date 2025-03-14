//
// Created by cris on 12/29/24.
//

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <Utils/Logger.h>
#include <Utils/Utils.hpp>

#include <map>
#include <memory>

class SceneBase;
class TextureManager;
class Registry;
class TileMap;

class SceneManager {
 public:
  SceneManager();
  ~SceneManager();

  auto Init() -> void;
  auto Events() -> void;
  auto Update(float deltaTime) -> void;
  auto SwitchScene(SceneSelect) -> void;

  std::shared_ptr<TextureManager> m_textureManager;
  std::shared_ptr<Registry> m_registry;
  std::shared_ptr<TileMap> m_tileMap;

  std::shared_ptr<SceneBase> m_currentScene;
  // std::unique_ptr<SceneBase> m_currentScene;
  std::map<SceneSelect, std::shared_ptr<SceneBase>> m_scenes;
  // std::map<SceneSelect, std::unique_ptr<SceneBase>> m_scenes;

  // std::vector<std::shared_ptr<IGameObject>> m_gameObjects;
};

#endif // SCENEMANAGER_HPP