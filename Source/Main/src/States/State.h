#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>

#include <memory>

#include "../Core/Node.h"

// #include "./GameStateManager.h"
class TextureManager;
class GameStateManager;

class State : public Node
{
  public:
	State(std::string_view name, GameStateManager& gsm, TextureManager& tm);
	virtual ~State( );

	virtual std::unique_ptr<State> Update(const float& deltaTime) = 0;
	virtual void Render( ) = 0;
	virtual void Load( ) = 0;
	virtual void Events(SDL_Event& event) = 0;

	virtual void EnterState( ) = 0;
	virtual void ExitState( ) = 0;

	void SetTextureManager(TextureManager& tm, std::string_view name = "new");

	void NewTextureManager(TextureManager* tm);

	GameStateManager& GetGameStateManager( ) const { return mGameStateManager; }

  protected:
	TextureManager& GetTextureManager( ) const { return mTextureManager; }

  private:
	// bool mIsRunning;
	TextureManager& mTextureManager;
	GameStateManager& mGameStateManager;
};

#endif	 // STATE_H
