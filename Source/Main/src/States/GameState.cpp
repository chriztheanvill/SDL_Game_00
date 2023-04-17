#include "GameState.h"

#include "GameStateManager.h"
#include "../Core/Engine.h"

#include <iostream>

GameState::GameState(GameStateManager& gsm, TextureManager& tm)
	: State("GameState", gsm, tm)
	, mLevel00(GetTextureManager( ))
{
	// Setting NODE
	SetName("GameState");
	// SetChild(&mPlayer);

	Logger::Debug(LogType::Log, "### GameState::Constructor :", GetName( ));

	// Load( );
}

GameState::~GameState( )
{
	//
	Logger::Debug(LogType::Log, "### ~GameState::Destructor :", GetName( ));
	// NodeLogComplete( );
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

void GameState::Load( )
{
	// ---------------------------------------------------------------
	// Texture Manager
	Logger::Debug(LogType::Debug, "GameState::Load");
	TextureManager tm;
	tm.SetName("TextureManager GameState Simple");
	tm.SetRender(*GetTextureManager( ).GetRender( ));
	GetTextureManager( ) = tm;

	// *GetGameStateManager( ).GetTextureManager( ) =
	// 	static_cast<TextureManager&&>(tm);	 // unique_ptr

	//
	// std::unique_ptr<TextureManager> tm =
	// std::make_unique<TextureManager>(this);

	// TextureManager* tm = new TextureManager;

	// tm->SetName("TextureManager GameState Unique_ptr");
	// tm->SetRender(GetGameStateManager( ).GetRender( ));
	// GetGameStateManager( ).GetTextureManager( ) = *tm;
	// GetGameStateManager( ).GetTextureManager( ) = *tm.release( ); // Unique

	GetTextureManager( ).Load("test", "assets/images/bkBlue.png");

	// ---------------------------------------------------------------
	// Levels
	mLevel00.SetTextureManager(&GetTextureManager( ));
	mLevel00.Init( );
}

// State* GameState::Update(const float& deltaTime)
std::unique_ptr<State> GameState::Update(const float& deltaTime)
// std::shared_ptr<State> GameState::Update(const float& deltaTime)
{
	Logger::Debug(LogType::Debug, "GameState::Update");

	mLevel00.Update(deltaTime);
	// mPlayer->Update(deltaTime);

	// return this;
	// if (GetGSM( ).GetMenuState( ))
	// {
	// 	std::cout << "\nGameState::Update::Return mMenuState;";
	// 	return GetGSM( ).GetMenuState( );
	// }
	return nullptr;
}

void GameState::Render( )
{
	//
	mLevel00.Render( );
}

void GameState::Events(SDL_Event& event)
{
	Logger::Debug(LogType::Debug, "GameState::Events");
	mLevel00.Events(event);
}

void GameState::EnterState( )
{
	Logger::Debug(LogType::Log,
				  "==================GameState::EnterState==================");
	Load( );
}

void GameState::ExitState( )
{
	Logger::Debug(LogType::Log,
				  "==================GameState::ExitState==================");
}
