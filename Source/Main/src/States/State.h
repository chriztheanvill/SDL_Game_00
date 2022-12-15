#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>

#include <memory>
// #include "./GameStateManager.h"
class GameStateManager;

class State
{
  public:
	State(GameStateManager& gsm);
	virtual ~State( );

	virtual std::shared_ptr<State> Update(const float& deltaTime) = 0;
	virtual void Render( ) = 0;
	virtual void Events(SDL_Event& event) = 0;

	virtual void EnterState( ) = 0;
	virtual void ExitState( ) = 0;

	inline bool GetIsRunning( ) const { return mIsRunning; }
	void SetIsRunning(const bool& running) { mIsRunning = running; }

  protected:
	GameStateManager& GetGSM( ) const { return mGSM; }

  private:
	bool mIsRunning;
	GameStateManager& mGSM;
};

#endif	 // STATE_H
