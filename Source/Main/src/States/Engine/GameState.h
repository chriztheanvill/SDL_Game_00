#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "./EngineState.hpp"

#include "../../Levels/LevelManager.hpp"

class TextureManager;

class GameState : public EngineState
{
  public:
	GameState(GameStateManager& gsm, TextureManager& tm);
	~GameState( ) override;

	void Load( ) override;
	// State* Update(const float& deltaTime) override;
	auto Update(const float& deltaTime)
		-> std::unique_ptr<EngineState> override;
	// std::shared_ptr<State> Update(const float& deltaTime) override;
	void Render( ) override;
	void Events(Controller& controller) override;

	void EnterState( ) override;
	void ExitState( ) override;

  private:
	LevelManager mLevelManager;
};

#endif	 // GAMESTATE_H
