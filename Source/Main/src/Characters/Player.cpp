#include "Player.h"
#include "../Core/TextureManager.h"

Player::Player(Node* node, TextureManager& tm)
	: Character(node, "Player")
{
	Logger::Debug(LogType::Log,
				  "--- GameState::Character::Player::Constructor ---");

	SetName("Player");

	Position( ).SetVector(Vector2D::Zero( ));
	// mPosition.SetVector({ 50, 10 });

	Collision( ) = { static_cast<int>(Position( ).GetX( )),
					 static_cast<int>(Position( ).GetY( )),
					 20,
					 20 };

	Size( ) = { static_cast<int>(GetSprite( ).GetSrc( ).x),
				static_cast<int>(GetSprite( ).GetSrc( ).y),
				0,
				0 };

	GetSprite( ).SetRenderer(tm.GetRender( ));
	GetSprite( ).SetTexture(tm.Load("Vivian", "assets/images/Vivian.jpg"));
	GetSprite( ).SetSrc({ 0, 0, 0, 0 });
	GetSprite( ).SetDst({ 0, 0, 100, 500 });
	// GetSprite( ).SetRenderer(tm->GetRender( ));
	// GetSprite( ).SetTexture(tm->Load("Vivian", "assets/images/Vivian.jpg"));
}

Player::~Player( )
{
	Logger::Debug(LogType::Log, "~GameState::Character::Player::Destructor");
	// NodeLogComplete( );
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

void Player::SetSprite(SDL_Texture* texture)
{
	GetSprite( ).SetTexture(texture);
}

void Player::Update(const float& deltaTime)
{
	GetRigidBody( ).Update(deltaTime);
	Position( ).Transform(GetRigidBody( ).Velocity( ));

	Logger::Debug(LogType::Debug,
				  "Player::mPlayer:",
				  " x: "sv,
				  Position( ).GetX( ),
				  " - y: "sv,
				  Position( ).GetY( ));

	Collision( ) = SDL_Rect { static_cast<int>(Position( ).GetX( )),
							  static_cast<int>(Position( ).GetY( )),
							  100,
							  150 };
}

void Player::Render( )
{
	// SDL_SetRenderDrawColor(mGameStateManager.GetEngine( ).GetRender( ),
	GetSprite( ).Render( );
}

void Player::Events(SDL_Event& event)
{
	Logger::Debug(LogType::Debug, "GameState::Events::Player");
	switch (event.type)
	{
		// case SDL_PRESSED:
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_d)
			{
				Logger::Debug(LogType::Log,
							  "GameState::Events::Player::Input::KeyDown::d");
				GetRigidBody( ).ApplyForceX(50);
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				Logger::Debug(LogType::Log,
							  "GameState::Events::Player::Input::KeyDown::a");
				GetRigidBody( ).ApplyForceX(-50);
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_d ||
				event.key.keysym.sym == SDLK_a)
			{
				Logger::Debug(
					LogType::Log,
					"++++++++++++++++GameState::Events::Player::UnsetX");
				GetRigidBody( ).UnsetForceX( );
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
