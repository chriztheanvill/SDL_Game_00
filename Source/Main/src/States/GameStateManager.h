#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <memory>

// #include "../States/State.h"
// class State;
// class GameState;
// class MenuState;
// #include "../Core/Engine.h"

#include "../Core/TextureManager.h"

class Engine;
class State;

class GameStateManager
{
  public:
	GameStateManager(SDL_Renderer& render);
	// GameStateManager(Engine& engine);
	~GameStateManager( );

	void Update(const float& deltaTime);

	std::unique_ptr<State> GetGameState( );

	std::unique_ptr<TextureManager>& GetTextureManager( )
	{
		return mTextureManager;
		// return *mTextureManager;
	}	//
	// TextureManager& GetTextureManager( ) { return *mTextureManager; }	//
	// THIS

	inline void SetIsRunning(const bool& run) { mIsRunning = run; }
	inline const bool& GetIsRunning( ) const { return mIsRunning; }

	// Engine& GetEngine( ) const { return mEngine; }

	SDL_Renderer& GetRender( ) const { return mRender; }
	// SDL_Renderer& GetRender( ) const { return *mRender; }

  private:
	SDL_Renderer& mRender;
	// SDL_Renderer* mRender;
	// Engine& mEngine;
	bool mIsRunning { };

	std::unique_ptr<TextureManager>
		mTextureManager;   // --------------------- THIS
	// TextureManager* mTextureManager;   // --------------------- THIS

	std::unique_ptr<State> mGameState;

	std::unique_ptr<State> mCurrent { };
	std::unique_ptr<State> mPrev { };

	// State* mCurrent { };
	// State* mPrev { };

	void Load( );
	void Events( );
	void Render( );
	void SetState(std::unique_ptr<State>& state);
	// void SetState(State* state);
};

/*
	shared_ptr
*/
// class GameStateManager
// {
//   public:
// 	GameStateManager(Engine& engine);
// 	~GameStateManager( );

// 	void Update(const float& deltaTime);

// 	std::shared_ptr<State> GetGameState( ) const { return mGameState; }
// 	std::shared_ptr<State> GetMenuState( ) const { return mMenuState; }

// 	inline void SetIsRunning(const bool& run) { mIsRunning = run; }
// 	inline const bool& GetIsRunning( ) const { return mIsRunning; }

// 	inline Engine& GetEngine( ) const { return mEngine; }

//   private:
// 	bool mIsRunning { };

// 	Engine& mEngine;
// 	std::shared_ptr<State> mGameState;
// 	std::shared_ptr<State> mMenuState;
// 	// std::shared_ptr<State> mStartState;

// 	std::shared_ptr<State> mCurrent;
// 	std::shared_ptr<State> mPrev;

// 	void Load( );
// 	void Events( );
// 	void Render( );
// 	void SetState(std::shared_ptr<State>& state);
// };

#endif	 // GAMESTATEMANAGER_H
