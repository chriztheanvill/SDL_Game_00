#include "GameState.h"

#include "GameStateManager.h"
#include "../Core/Engine.h"

#include <iostream>

GameState::GameState(GameStateManager& gsm)
	: State(gsm)
	, mPlayer(this, gsm)
	, Node(nullptr)
// , mPlayer(nullptr, gsm)
{
	// Setting NODE
	SetName("GameState");
	SetChild(&mPlayer);

	// TextureManager
	// GetGameStateManager( ).GetTextureManager( ) =
	// 	TextureManager(GetGameStateManager( ).GetEngine( ));

	// TextureManager tm(GetGameStateManager( ).GetEngine( ));

	std::cout << "\n ### GameState::Constructor ### \n";

	Load( );
}

GameState::~GameState( )
{
	//
	std::cout << "\n~GameState::Destructor";
	// DeleteChildren( );
}

void GameState::Load( )
{
	// GetGameStateManager( ).TextureManagerGame( ).Load(
	GetGameStateManager( ).GetTextureManager( ).Load(
		"test",
		"assets/images/bkBlue.png");

	mPlayer.SetSprite("Vivian", "assets/images/Vivian.jpg");
}

// State* GameState::Update(const float& deltaTime)
std::unique_ptr<State> GameState::Update(const float& deltaTime)
// std::shared_ptr<State> GameState::Update(const float& deltaTime)
{
	std::cout << "\nGameState::Update";

	mPlayer.Update(deltaTime);

	// return this;
	// if (GetGSM( ).GetMenuState( ))
	// {
	// 	std::cout << "\nGameState::Update::Return mMenuState;";
	// 	return GetGSM( ).GetMenuState( );
	// }
	return nullptr;
}

void GameState::Render( ) { mPlayer.Render( ); }

void GameState::Events(SDL_Event& event)
{
	std::cout << "\nGameState::Events";
	mPlayer.Events(event);
}

void GameState::EnterState( )
{
	std::cout
		<< "\n==================GameState::EnterState==================\n\n";
}

void GameState::ExitState( )
{
	std::cout
		<< "\n==================GameState::ExitState==================\n\n";
}
