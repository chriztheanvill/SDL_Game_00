#include "GameStateManager.h"

#include "../States/State.h"
#include "./GameState.h"
#include "./MenuState.h"
#include "../Core/Engine.h"
#include "../Core/TextureManager.h"

#include <iostream>

// GameStateManager::GameStateManager(Engine& engine)
GameStateManager::GameStateManager(SDL_Renderer& render)
	:	//
	// Shared
	// : mGameState(std::make_shared<GameState>(*this))
	// , mMenuState(std::make_shared<MenuState>(*this))
	mRender(render)
	// mRender(&render)
	// mEngine(engine)
	, mTextureManager(std::make_unique<TextureManager>( ))
{
	std::cout << "\n--- GameStateManager::Constructor --- \n";
	Load( );
}

GameStateManager::~GameStateManager( )
{
	if (mCurrent) mCurrent->ExitState( );

	delete mCurrent;
	delete mPrev;
	// delete mTextureManager;
	mCurrent = nullptr;
	mPrev = nullptr;
	// mTextureManager = nullptr;
	std::cout << "\n\n--- ~GameStateManager \n";
}

void GameStateManager::Load( )
{
	// if (!mRender)
	// {
	// 	std::cout << "\n\nGameStateManager::Load No Render!!! \n";
	// 	return;
	// }
	mGameState = std::make_unique<MenuState>(*this);
	mGameState->SetName("MenuState");
	// mTextureManager.SetRender(*mEngine.GetRender( ));
	// mTextureManager.SetParent(mGameState.get( ));
	// mTextureManager->SetName("Texture Manager MenuState");
	// mTextureManager->SetRender(*mEngine.GetRender( ));
	// mTextureManager->SetParent(mGameState.get( ));

	// mTextureManagerSystem.Load("");	  // ERROR: Assert

	mIsRunning = true;

	if (mGameState) SetState(mGameState.release( ));   // Unique
	// if (mGameState) SetState(mGameState.get( ));   // Unique
	else
	{
		std::cout
			<< "\n--- GameStateManager::Constructor ERROR!!! No state --- \n";
		exit(1);
	}
	// SetState(mGameState); // Shared
}

std::unique_ptr<State> GameStateManager::GetGameState( )
{
	// return new GameState(*this);
	// return std::unique_ptr<GameState>(this);
	std::unique_ptr<GameState> tmp = std::make_unique<GameState>(*this);
	// tmp->SetParent(*this);
	return tmp;
	// return std::make_unique<GameState>(*this);
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
			std::cout
				<< "\n+++ GameStateManager::Update Updating +++ tmp: "	 //
				<< tmp << " - " << tmp->GetName( ) << "\n";
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
	// SDL_SetRenderDrawColor(mEngine.GetRender( ), 60, 60, 60, 255);
	// SDL_RenderClear(mEngine.GetRender( ));
	SDL_SetRenderDrawColor(&mRender, 60, 60, 60, 255);
	// SDL_SetRenderDrawColor(mRender, 60, 60, 60, 255);
	SDL_RenderClear(&mRender);
	// SDL_RenderClear(mRender);

	/* ################################################# */
	// Game

	mCurrent->Render( );

	/* ################################################# */

	// System
	// Clean the screen
	SDL_RenderPresent(&mRender);
	// SDL_RenderPresent(mRender);
	// SDL_RenderPresent(mEngine.GetRender( ));
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
		   "################################### \n";

	if (mPrev)
	{
		std::cout << "\nmPrev: " << mPrev << " - " << mPrev->GetName( ) << "\n";
		mPrev->ExitState( );
	}
	if (mCurrent)
	{
		std::cout << "\nmCurrent: " << mCurrent << " - " << mCurrent->GetName( )
				  << "\n";
		mCurrent->EnterState( );
	}
}