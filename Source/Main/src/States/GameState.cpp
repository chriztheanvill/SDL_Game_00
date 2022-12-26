#include "GameState.h"

#include "GameStateManager.h"
#include "../Core/Engine.h"

#include <iostream>

GameState::GameState(GameStateManager& gsm)
	: State(gsm)
	, mPlayer(gsm)
{
	std::cout << "\n ### GameState::Constructor ### \n";
	GetGameStateManager( ).TextureManagerGame( ).Load(
		"test",
		"assets/images/bkBlue.png");
}

GameState::~GameState( ) {}

State* GameState::Update(const float& deltaTime)
// std::unique_ptr<State> GameState::Update(const float& deltaTime)
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

void GameState::EnterState( ) { std::cout << "\nGameState::EnterState"; }

void GameState::ExitState( ) { std::cout << "\nGameState::ExitState"; }
