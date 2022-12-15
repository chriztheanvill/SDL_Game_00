#include "MenuState.h"

#include "GameStateManager.h"
#include "../Core/Engine.h"

#include <iostream>

MenuState::MenuState(GameStateManager& gsm)
	: State(gsm)
{
	std::cout << "\n ### MenuState::Constructor ### \n";
}

MenuState::~MenuState( ) {}

State* MenuState::Update(const float& deltaTime)
// std::unique_ptr<State> MenuState::Update(const float& deltaTime)
// std::shared_ptr<State> MenuState::Update(const float& deltaTime)
{
	std::cout << "\nMenuState::Update";
	if (&GetGSM( ).GetGameState( ))
	{
		std::cout << "\nMenuState::Update::Return GetGameState;";
		return &GetGSM( ).GetGameState( );
		// return std::make_unique<State>(GetGSM( ).GetGameState( ));
	}
	// if (GetGSM( ).GetGameState( ))
	// {
	// 	std::cout << "\nMenuState::Update::Return GetGameState;";
	// 	return GetGSM( ).GetGameState( );
	// }
	return nullptr;
}

void MenuState::Render( )
{
	// SDL_Rect player = { 10, 10, 20, 20 };
	// SDL_SetRenderDrawColor(GetGSM( ).GetEngine( ).GetRender( ), 0, 0, 0,
	// 255); SDL_RenderFillRect(GetGSM( ).GetEngine( ).GetRender( ), &player);
}

void MenuState::Events(SDL_Event& event) {}

void MenuState::EnterState( ) { std::cout << "\nMenuState::EnterState"; }

void MenuState::ExitState( ) { std::cout << "\nMenuState::ExitState"; }
