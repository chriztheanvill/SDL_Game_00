#include "GameStateManager.h"
#include "./GameState.h"
#include "./MenuState.h"
#include "../Core/Engine.h"

#include <iostream>

GameStateManager::GameStateManager(Engine& engine)
	: mGameState(std::make_shared<GameState>(*this))
	, mMenuState(std::make_shared<MenuState>(*this))
	, mEngine(engine)
// , mStartState(std::make_shared<State>( ))
{
	Load( );
	SetState(mGameState);
}

GameStateManager::~GameStateManager( ) { mCurrent->ExitState( ); }

void GameStateManager::Update(const float& deltaTime)
{
	// std::cout << "\nDeltaTime: " << deltaTime;
	if (mCurrent && mIsRunning)
	{
		Events( );
		std::shared_ptr<State> tmp = mCurrent->Update(deltaTime);
		std::cout << "\n---Update --- tmp: " << tmp << "\n";
		Render( );
		if (tmp)
		{
			std::cout << "\n+++ Updating:\n tmp: " << tmp << "\n";
			SetState(tmp);
		}
	}
}

void GameStateManager::Load( )
{
	//
}

void GameStateManager::Render( )
{
	// System
	SDL_SetRenderDrawColor(mEngine.GetRender( ), 60, 60, 60, 255);
	SDL_RenderClear(mEngine.GetRender( ));

	/* ################################################# */
	// Game

	mCurrent->Render( );

	/* ################################################# */

	// System
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

void GameStateManager::SetState(std::shared_ptr<State>& state)
{
	mPrev = mCurrent;
	mCurrent = state;
	// mCurrent = std::move(state);

	if (mPrev) mPrev->ExitState( );
	if (mCurrent) mCurrent->EnterState( );
}