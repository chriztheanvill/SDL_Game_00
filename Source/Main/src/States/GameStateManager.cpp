#include "GameStateManager.h"

#include "../States/State.h"
#include "./GameState.h"
#include "./MenuState.h"
#include "../Core/Engine.h"
#include "../Core/TextureManager.h"

#include <iostream>

GameStateManager::GameStateManager(Engine& engine)
	// : mTextureManagerMenu(engine)
	// , mTextureManagerSystem(engine)
	// , mTextureManagerGame(engine)
	: mTextureManager(engine)
	//
	// , mGameState(std::make_unique<GameState>(*this))
	// , mGameState(std::make_unique<MenuState>(*this))
	// , mMenuState(std::make_unique<MenuState>(*this))
	// Shared
	// : mGameState(std::make_shared<GameState>(*this))
	// , mMenuState(std::make_shared<MenuState>(*this))
	, mEngine(engine)
// , mStartState(std::make_shared<State>( ))
{
	std::cout << "\n--- GameStateManager::Constructor --- \n";
	Load( );
	mIsRunning = true;
	SetState(mGameState.release( ));   // Unique
	// SetState(mGameState.get( ));   // Unique
	// SetState(mGameState); // Shared
}

GameStateManager::~GameStateManager( )
{
	if (mCurrent) mCurrent->ExitState( );

	mCurrent = nullptr;
	mPrev = nullptr;
	mGameState = nullptr;
	// mMenuState = nullptr;
	std::cout << "\n\n--- ~GameStateManager \n";
}

std::unique_ptr<State> GameStateManager::GetGameState( )
{
	// return new GameState(*this);
	// return std::unique_ptr<GameState>(this);
	return std::make_unique<GameState>(*this);
}

void GameStateManager::Load( )
{
	mGameState = std::make_unique<MenuState>(*this);

	//
	// mTextureManagerSystem.Load("");	  // ERROR: Assert
}

// State* GameStateManager::GetGameState( )
// {
// 	// return new GameState(*this);
// 	return std::unique_ptr<GameState>(*this);
// 	// return std::make_unique<GameState>(*this);
// }

void GameStateManager::Update(const float& deltaTime)
{
	// std::cout << "\nDeltaTime: " << deltaTime;

	if (mCurrent && mIsRunning)
	{
		Events( );
		// Switching between Game modes: (Main menu, Game, Pause)
		// State* tmp = mCurrent->Update(deltaTime);
		std::unique_ptr<State> tmp = mCurrent->Update(deltaTime);
		// std::shared_ptr<State> tmp = mCurrent->Update(deltaTime);
		// std::cout << "\n---GameStateManager::Update --- tmp: " << tmp <<
		// "\n";
		Render( );
		if (tmp)
		{
			std::cout << "\n+++ GameStateManager::Update Updating +++ tmp: "
					  << tmp << "\n";
			// SetState(tmp);
			SetState(tmp.release( ));
			// SetState(tmp.get( ));
		}
	}
}

void GameStateManager::Render( )
{
	// System
	// Paint color
	SDL_SetRenderDrawColor(mEngine.GetRender( ), 60, 60, 60, 255);
	SDL_RenderClear(mEngine.GetRender( ));

	/* ################################################# */
	// Game

	mCurrent->Render( );

	/* ################################################# */

	// System
	// Clean the screen
	SDL_RenderPresent(mEngine.GetRender( ));
}

void GameStateManager::Events( )
{
	SDL_Event event { };
	while (SDL_PollEvent(&event))
	{
		/* ======== SYSTEM ======== */
		switch (event.type)
		{
			case SDL_QUIT: mIsRunning = false; break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_q ||
					event.key.keysym.sym == SDLK_ESCAPE)
				{
					mIsRunning = false;
					std::cout << "\n\nQuitting game by Q.\n";
				}
		}
		/* ======== ~SYSTEM ======== */

		/* ======== Game ======== */
		mCurrent->Events(event);
		/* ======== ~Game ======== */
	}
	//
}

void GameStateManager::SetState(State* state)
// void GameStateManager::SetState(std::unique_ptr<State>& state)
// void GameStateManager::SetState(std::unique_ptr<State> state)
// void GameStateManager::SetState(std::shared_ptr<State>& state)
{
	mPrev = std::move(mCurrent);
	mCurrent = std::move(state);

	// mPrev = mCurrent;
	// mCurrent = state;
	// // mCurrent = std::move(state);

	std::cout
		<< "\n ################################### GameStateManager::SetState "
		   "################################### \nmCurrent: "
		<< mCurrent << "\nmPrev: " << mPrev << "\n";

	if (mPrev) mPrev->ExitState( );
	if (mCurrent) mCurrent->EnterState( );
}