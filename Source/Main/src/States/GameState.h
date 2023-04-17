#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "./State.h"

#include "../Levels/Level.h"

class TextureManager;

class GameState : public State
{
  public:
	GameState(GameStateManager& gsm, TextureManager& tm);
	~GameState( ) override;

	void Load( ) override;
	// State* Update(const float& deltaTime) override;
	std::unique_ptr<State> Update(const float& deltaTime) override;
	// std::shared_ptr<State> Update(const float& deltaTime) override;
	void Render( ) override;
	void Events(SDL_Event& event) override;

	void EnterState( ) override;
	void ExitState( ) override;

  private:
	Level mLevel00;
};

#endif	 // GAMESTATE_H
