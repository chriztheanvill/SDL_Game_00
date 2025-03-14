//
// Created by cris on 12/29/24.
//

#include "SceneManager.hpp"

#include "Scene00.hpp"
#include "SceneShip00.hpp"

#include <ranges>

SceneManager::SceneManager() {
  Logger::Debug(LogType::Log, "### SceneManager::SceneManager: ");

  m_scenes[SceneSelect::Scene_00] = std::make_shared<Scene00>();
  m_scenes[SceneSelect::Scene_01] = std::make_shared<SceneShip00>();

  for (auto& eachScene: m_scenes | std::views::values) { eachScene->m_sceneManager = this; }
}

SceneManager::~SceneManager() {
  Logger::Debug(LogType::Log, "### SceneManager::~SceneManager: ");
  m_currentScene->Exit();

  // for (auto& eachScenario: m_scenes | std::views::values) {
  //   eachScenario->m_sceneManager = nullptr;
  // }
}

auto SceneManager::Init() -> void {
  m_currentScene = m_scenes.at(SceneSelect::Scene_00);
  // m_currentScene = std::move(m_scenes.at(SceneSelect::Scene_00));
  m_currentScene->Enter();

  // m_registry->Update();
}

auto SceneManager::Events() -> void { m_currentScene->Events(); }

auto SceneManager::Update(float deltaTime) -> void { m_currentScene->Update(deltaTime); }

auto SceneManager::SwitchScene(SceneSelect scene) -> void {
  m_currentScene->Exit();

  m_currentScene = m_scenes.at(scene);
  // m_currentScene = std::move(m_scenes.at(scene));

  m_currentScene->Enter();
}