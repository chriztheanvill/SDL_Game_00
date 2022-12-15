#include "GameState.h"

#include "GameStateManager.h"
#include "../Core/Engine.h"

#include <iostream>
#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

RigidBody velocity;
Vector2D player;

GameState::GameState(GameStateManager& gsm)
	: State(gsm)
{
	std::cout << "\n ### GameState::Constructor ### \n";
	player.SetX(50);
}

GameState::~GameState( ) {}

std::shared_ptr<State> GameState::Update(const float& deltaTime)
{
	std::cout << "\nGameState::Update";

	velocity.Update(deltaTime);
	velocity.ApplyForceX(100);

	player.TransformX(velocity.GetPos( ).GetX( ));
	player.TransformY(velocity.GetPos( ).GetY( ));

	// if (gsm.GetMenuState( ))
	// {
	// 	std::cout << "\nGameState::Update::Return mMenuState;";
	// 	return gsm.GetMenuState( );
	// }
	return nullptr;
}

void GameState::Render( )
{
	SDL_Rect rendplayer = { static_cast<int>(player.GetX( )),
							static_cast<int>(player.GetY( )),
							200,
							200 };
	SDL_SetRenderDrawColor(GetGSM( ).GetEngine( ).GetRender( ), 0, 0, 0, 255);

	SDL_RenderFillRect(GetGSM( ).GetEngine( ).GetRender( ), &rendplayer);
}

void GameState::Events(SDL_Event& event)
{
	std::cout << "\nGameState::Events";
	switch (event.type)
	{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w)
			{
				std::cout << "\nGameState::Events::Input::w";
			}
	}
}

void GameState::EnterState( ) { std::cout << "\nGameState::EnterState"; }

void GameState::ExitState( ) { std::cout << "\nGameState::ExitState"; }
