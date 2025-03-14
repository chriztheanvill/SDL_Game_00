//
// Created by cris on 12/29/24.
//

#ifndef SCENE00_HPP
#define SCENE00_HPP

#include "SceneBase.hpp"

class Player;

class Scene00 : public SceneBase {
  // Entity m_player;
  // Entity m_enemy_01;
  // bool m_btnPress {};

  // std::unique_ptr<Player> m_player;

 public:
  Scene00();
  virtual ~Scene00();

  auto Enter() -> void override;
  auto Exit() -> void override;
  // auto Update(float deltaTime) -> void override;
};

#endif // SCENE00_HPP