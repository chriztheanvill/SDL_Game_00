#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "./State.h"

#include "../Characters/Player.h"

class TextureManager;

class GameState : public State
{
  public:
	GameState(GameStateManager& gsm);
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
	std::unique_ptr<Player> mPlayer;
	// Player mPlayer;
	// TextureManager* mTextureManager;
	std::unique_ptr<TextureManager> tm;
};

#endif	 // GAMESTATE_H
