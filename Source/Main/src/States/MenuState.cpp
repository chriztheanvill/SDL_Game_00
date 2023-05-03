#include "MenuState.h"

#include "GameStateManager.h"

#include <iostream>

MenuState::MenuState(GameStateManager& gsm, TextureManager& tm)
	: State("MenuState", gsm, tm)
{
	Logger::Debug(LogType::Log, "### MenuState::Constructor : ", GetName( ));
}

MenuState::~MenuState( )
{
	Logger::Debug(LogType::Log, "### MenuState::Destructor : ", GetName( ));
	// NodeLogComplete( );
}

void MenuState::Load( )
{
	// mPlayer.SetSprite("Vivian", "assets/images/Vivian.jpg");
}

std::unique_ptr<State> MenuState::Update(const float& deltaTime)
{
	Logger::Debug(LogType::Debug, "MenuState::Update");
	Logger::Debug(LogType::Debug, "MenuState::Update::Return GameState");
	return GetGameStateManager( ).NewGameState( );
	// return std::make_unique<State>(GetGSM( ).GetGameState( ));

	// if (&GetGameStateManager( ).GetGameState( )) // Reference, if is alive
	// {
	// 	std::cout << "\nMenuState::Update::Return GetGameState;";
	// 	return &GetGameStateManager( ).GetGameState( );
	// 	// return std::make_unique<State>(GetGSM( ).GetGameState( ));
	// }
	// if (GetGSM( ).GetGameState( ))
	// {
	// 	std::cout << "\nMenuState::Update::Return GetGameState;";
	// 	return GetGSM( ).GetGameState( );
	// }
	Logger::Debug(LogType::Warning,
				  "MenuState::Update::Return Nullptr !!!!!!!!!!!!!!");
	return nullptr;
}

void MenuState::Render( )
{
	// SDL_Rect player = { 10, 10, 20, 20 };
	// SDL_SetRenderDrawColor(GetGSM( ).GetEngine( ).GetRender( ), 0, 0, 0,
	// 255); SDL_RenderFillRect(GetGSM( ).GetEngine( ).GetRender( ), &player);
}

void MenuState::Events(Controller& controller) {}

void MenuState::EnterState( )
{
	Logger::Debug(LogType::Debug,
				  "==================MenuState::EnterState==================");
}

void MenuState::ExitState( )
{
	Logger::Debug(LogType::Debug,
				  "==================MenuState::ExitState==================");
}
