#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "./State.h"

class GameState : public State
{
  public:
	GameState(GameStateManager& gsm);
	~GameState( ) override;

	std::shared_ptr<State> Update(const float& deltaTime) override;
	void Render( ) override;
	void Events(SDL_Event& event) override;

	void EnterState( ) override;
	void ExitState( ) override;

  private:
};

#endif	 // GAMESTATE_H
