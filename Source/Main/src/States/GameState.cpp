#include "GameState.h"

#include "GameStateManager.h"
#include "../Core/Engine.h"

#include <iostream>
#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

RigidBody velocity;
Vector2D player { };

SDL_Rect rendplayer { };

GameState::GameState(GameStateManager& gsm)
	: State(gsm)
{
	std::cout << "\n ### GameState::Constructor ### \n";
	player.SetY(0);
	player.SetX(250);
}

GameState::~GameState( ) {}

State* GameState::Update(const float& deltaTime)
// std::unique_ptr<State> GameState::Update(const float& deltaTime)
// std::shared_ptr<State> GameState::Update(const float& deltaTime)
{
	std::cout << "\nGameState::Update";

	velocity.Update(deltaTime);
	// velocity.ApplyForceX(5);
	// velocity.ApplyForceY(500);

	player.TransformX(velocity.GetVelocity( ).GetX( ));
	player.TransformY(velocity.GetVelocity( ).GetY( ));
	// player.TransformX(velocity.GetPos( ).GetX( ));
	// player.TransformY(velocity.GetPos( ).GetY( ));

	fmt::print("player x: {}, y: {}", player.GetX( ), player.GetY( ));

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
	rendplayer = { static_cast<int>(player.GetX( )),
				   static_cast<int>(player.GetY( )),
				   20,
				   20 };
	SDL_SetRenderDrawColor(GetGSM( ).GetEngine( ).GetRender( ),
						   255,
						   255,
						   255,
						   255);

	SDL_RenderFillRect(GetGSM( ).GetEngine( ).GetRender( ), &rendplayer);
}

void GameState::Events(SDL_Event& event)
{
	std::cout << "\nGameState::Events";
	switch (event.type)
	{
		// case SDL_PRESSED:
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_d)
			{
				std::cout << "\nGameState::Events::Input::KeyDown::d";
				velocity.ApplyForceX(50);
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				std::cout << "\nGameState::Events::Input::KeyDown::a";
				velocity.ApplyForceX(-50);
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_d ||
				event.key.keysym.sym == SDLK_a)
			{
				std::cout << "\n++++++++++++++++GameState::Events::UnsetX";
				velocity.UnsetForceX( );
			}
			break;

			// if (event.key.keysym.sym == SDLK_w)
			// {
			// 	std::cout << "\nGameState::Events::Input::w";
			// }
			// else if (event.key.keysym.sym == SDLK_s)
			// {
			// 	std::cout << "\nGameState::Events::Input::s";
			// }
			// else
			// {
			// 	std::cout << "\nGameState::Events::UnsetY";
			// 	velocity.UnsetForceY( );
			// }
	}
}

void GameState::EnterState( ) { std::cout << "\nGameState::EnterState"; }

void GameState::ExitState( ) { std::cout << "\nGameState::ExitState"; }
