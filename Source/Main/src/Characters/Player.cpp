#include "Player.h"
#include <fmt/color.h>
#include "../States/GameStateManager.h"
#include "../Core/Engine.h"

Player::Player(GameStateManager& gsm)
	: mGameStateManager(gsm)
{
	fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua),
			   "\n--- Player::Constructor ---\n");
	mPosition.SetVector(Vector2D::Zero( ));
	// mPosition.SetVector({ 50, 10 });

	mCollision = { static_cast<int>(mPosition.GetX( )),
				   static_cast<int>(mPosition.GetX( )),
				   20,
				   20 };

	mPlayerTexture = mGameStateManager.TextureManagerGame( ).Load(
		"Vivian",
		"assets/images/Vivian.jpg");
}

Player::~Player( ) {}

void Player::Update(const float& deltaTime)
{
	mRigidBody.Update(deltaTime);
	mPosition.Transform(mRigidBody.Velocity( ));

	fmt::print("\nPlayer::mPlayer x: {}, y: {}",
			   Position( ).GetX( ),
			   Position( ).GetY( ));

	mCollision = SDL_Rect { static_cast<int>(mPosition.GetX( )),
							static_cast<int>(mPosition.GetY( )),
							100,
							150 };
}

void Player::Render( )
{
	SDL_SetRenderDrawColor(mGameStateManager.GetEngine( ).GetRender( ),
						   255,
						   255,
						   255,
						   255);

	SDL_RenderFillRect(mGameStateManager.GetEngine( ).GetRender( ),
					   &mCollision);

	SDL_RenderCopy(mGameStateManager.GetEngine( ).GetRender( ),
				   mPlayerTexture,
				   nullptr,
				   &mCollision);
}

void Player::Events(SDL_Event& event)
{
	std::cout << "\nGameState::Events::Player";
	switch (event.type)
	{
		// case SDL_PRESSED:
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_d)
			{
				std::cout << "\nGameState::Events::Player::Input::KeyDown::d";
				mRigidBody.ApplyForceX(50);
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				std::cout << "\nGameState::Events::Player::Input::KeyDown::a";
				mRigidBody.ApplyForceX(-50);
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_d ||
				event.key.keysym.sym == SDLK_a)
			{
				std::cout
					<< "\n++++++++++++++++GameState::Events::Player::UnsetX";
				mRigidBody.UnsetForceX( );
			}
			break;

			//
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
