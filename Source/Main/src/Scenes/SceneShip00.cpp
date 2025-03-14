//
// Created by cris on 12/29/24.
//

#include "SceneShip00.hpp"
#include "SceneManager.hpp"

SceneShip00::SceneShip00() {
  Logger::Debug(LogType::Log, "SceneShip00::SceneShip00: ");
}

SceneShip00::~SceneShip00() {
  Logger::Debug(LogType::Log, "SceneShip00::~SceneShip00: ");
}

auto SceneShip00::Enter() -> void { Logger::Debug(LogType::Log, "SceneShip00::Enter: "); }

auto SceneShip00::Exit() -> void { Logger::Debug(LogType::Log, "SceneShip00::Exit: "); }

auto SceneShip00::Update(float deltaTime) -> void {
  Logger::Debug(LogType::Log, "SceneShip00::Update: ");
  m_sceneManager->SwitchScene(SceneSelect::Scene_00);
}