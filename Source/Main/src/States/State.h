#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>

#include <memory>

#include "../Core/Node.h"

// #include "./GameStateManager.h"
class GameStateManager;

class State : public Node
{
  public:
	State(GameStateManager& gsm, const std::string& name = "");
	virtual ~State( );

	// virtual State* Update(const float& deltaTime) = 0;
	virtual std::unique_ptr<State> Update(const float& deltaTime) = 0;
	// virtual std::shared_ptr<State> Update(const float& deltaTime) = 0;
	virtual void Render( ) = 0;
	virtual void Load( ) = 0;
	virtual void Events(SDL_Event& event) = 0;

	virtual void EnterState( ) = 0;
	virtual void ExitState( ) = 0;

	// inline bool GetIsRunning( ) const { return mIsRunning; }
	// void SetIsRunning(const bool& running) { mIsRunning = running; }

  protected:
	GameStateManager& GetGameStateManager( ) const { return mGameStateManager; }

  private:
	// bool mIsRunning;
	GameStateManager& mGameStateManager;
};

#endif	 // STATE_H
