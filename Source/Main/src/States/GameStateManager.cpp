#include "GameStateManager.h"

#include "../States/State.h"
#include "./GameState.h"
#include "./MenuState.h"

GameStateManager::GameStateManager( )
{
	Logger::Debug(LogType::Log, "--- GameStateManager::Constructor ---");
}

GameStateManager::~GameStateManager( )
{
	if (mCurrent) mCurrent->ExitState( );

	mCurrent = nullptr;
	mPrev = nullptr;
	Logger::Debug(LogType::Log, "--- ~GameStateManager ---");
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

void GameStateManager::Load( )
{
	// Graphics
	// mTextureManager->SetName("Texture Manager MenuState");
	// mTextureManager->SetRender(*mGraphics.GetRender( ));
	// mTextureManager->SetParent(mGameState.get( ));

	mTextureManager.SetName("TextureManager::MenuState");

	// Game States
	mGameState = std::make_unique<MenuState>(*this, mTextureManager);
	mGameState->SetName("MenuState");

	mIsRunning = true;

	if (mGameState) { SetState(mGameState); }
	else
	{
		Logger::Debug(LogType::Error,
					  "GameStateManager::Constructor ERROR!!! No state ---");
		exit(1);
	}
}

// --------------------------------------------------------------------------------------
std::unique_ptr<State> GameStateManager::NewGameState( )
{
	// TODO Checar esta funcion
	// Seria mas limpio
	// mGameState = std::make_unique<GameState>(*this, mTextureManager);
	// Seria mas limpio

	mTextureManager.SetName("TextureManager::GameState");
	std::unique_ptr<GameState> tmpReturn =
		std::make_unique<GameState>(*this, mTextureManager);
	// tmpReturn->SetTextureManager(mTextureManager,
	// "GameState::TextureManager");

	return tmpReturn;
	// return std::make_unique<GameState>( );
}

// --------------------------------------------------------------------------------------
void GameStateManager::Update(const float& deltaTime)
{
	Logger::Debug(LogType::Log, "DeltaTime: ", deltaTime);

	if (mCurrent && mIsRunning)
	{
		Events( );

		// Switching between Game modes: (Main menu, Game, Pause)
		std::unique_ptr<State> tmp = mCurrent->Update(deltaTime);
		Render( );
		if (tmp)
		{
			Logger::Debug(LogType::Debug,
						  "GameStateManager::Update Updating +++ tmp: ",
						  &tmp,
						  " - ",
						  tmp->GetName( ));

			SetState(tmp);
		}
	}
}

void GameStateManager::Render( )
{
	// Paint color
	SDL_SetRenderDrawColor(mTextureManager.GetRender( ), 60, 60, 60, 255);
	SDL_RenderClear(mTextureManager.GetRender( ));

	/* ################################################# */

	mCurrent->Render( );

	/* ################################################# */

	// Clean the screen
	SDL_RenderPresent(mTextureManager.GetRender( ));
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
					Logger::Debug(LogType::Log, "Quitting game by Q.");
				}
		}
		/* ======== ~SYSTEM ======== */

		/* ======== Game ======== */
		mCurrent->Events(event);
		/* ======== ~Game ======== */
	}
	//
}

void GameStateManager::SetState(std::unique_ptr<State>& state)
{
	mPrev = std::move(mCurrent);
	mCurrent = std::move(state);

	// mPrev = mCurrent;
	// mCurrent = state;
	// // mCurrent = std::move(state);

	Logger::Debug(LogType::Log, "GameStateManager::SetState");

	if (mPrev)
	{
		Logger::Debug(LogType::Debug,
					  "GameStateManager::SetState mPrev: ",
					  &mPrev,
					  " - "s,
					  mPrev->GetName( ));
		// std::cout << "\nmPrev: " << &mPrev << " - " << mPrev->GetName( )
		// 		  << "\n";
		mPrev->ExitState( );
	}

	if (mCurrent)
	{
		Logger::Debug(LogType::Debug,
					  "GameStateManager::SetState mCurrent: ",
					  &mCurrent,
					  " - "s,
					  mCurrent->GetName( ));
		// std::cout << "\nmCurrent: " << &mCurrent << " - "
		// 		  << mCurrent->GetName( ) << "\n";
		mCurrent->EnterState( );
	}
}