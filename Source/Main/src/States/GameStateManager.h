#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

// #include "../States/State.h"
// class State;
// class GameState;
// class MenuState;
// #include "../Core/Engine.h"

#include "../Core/TextureManager.h"

class State;

class GameStateManager
{
  public:
	GameStateManager( );
	~GameStateManager( );

	void Update(const float& deltaTime);

	std::unique_ptr<State> NewGameState( );

	void SetTextureManagerRenderer(SDL_Renderer* render)
	{
		mTextureManager.SetRender(*render);
	}
	TextureManager& GetTextureManager( ) { return mTextureManager; }

	inline void SetIsRunning(const bool& run) { mIsRunning = run; }
	inline const bool& GetIsRunning( ) const { return mIsRunning; }

	void Load( );

  private:
	bool mIsRunning { };

	TextureManager mTextureManager;

	std::unique_ptr<State> mGameState;
	std::unique_ptr<State> mCurrent { };
	std::unique_ptr<State> mPrev { };

	void Events( );
	void Render( );
	void SetState(std::unique_ptr<State>& state);
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
