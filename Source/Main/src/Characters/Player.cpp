#include "Player.h"
#include "../Graphics/TextureManager.h"

Player::Player(Node* node, TextureManager& tm)
	: Character(node, "Player")
{
	Logger::Debug(LogType::Log,
				  "--- GameState::Character::Player::Constructor ---");

	Position( ).SetVector(Vector2D::Zero( ));
	// mPosition.SetVector({ 50, 10 });

	Size( ) = { 100, 500 };
	Collision( ) = {
		static_cast<int>(Position( ).GetX( )),
		static_cast<int>(Position( ).GetY( )),
		static_cast<int>(Size( ).GetX( )),
		static_cast<int>(Size( ).GetY( )),
	};

	GetSprite( ).SetName("Sprite::Player");
	GetSprite( ).SetRenderer(tm.GetRender( ));
	GetSprite( ).SetTexture(tm.Load("Vivian", "assets/images/Vivian.jpg"));
	GetSprite( ).SetSrc({ });
	GetSprite( ).SetDst({ static_cast<int>(Position( ).GetX( )),
						  static_cast<int>(Position( ).GetY( )),
						  static_cast<int>(Size( ).GetX( )),
						  static_cast<int>(Size( ).GetY( )) });
	// GetSprite( ).SetDst({ 0, 0, 100, 300 });

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
	mRigidBody.Update(deltaTime);
	Position( ).Transform(mRigidBody.Velocity( ));

	Logger::Debug(LogType::Debug,
				  "Player::mPlayer:",
				  " x: "sv,
				  Position( ).GetX( ),
				  " - y: "sv,
				  Position( ).GetY( ));

	Collision( ) = {
		static_cast<int>(Position( ).GetX( )),
		static_cast<int>(Position( ).GetY( )),
		static_cast<int>(Size( ).GetX( )),
		static_cast<int>(Size( ).GetY( )),
	};

	GetSprite( ).SetDst({ static_cast<int>(Position( ).GetX( )),
						  static_cast<int>(Position( ).GetY( )),
						  static_cast<int>(Size( ).GetX( )),
						  static_cast<int>(Size( ).GetY( )) });
}

void Player::Render( )
{
	// SDL_SetRenderDrawColor(mGameStateManager.GetEngine( ).GetRender( ),
	GetSprite( ).Render( );
}

void Player::Events(Controller& controller)
{
	Logger::Debug(LogType::Debug, "GameState::Events::Player");

	if (controller.MoveRight( ))
	{
		Logger::Debug(LogType::Warning,
					  "GameState::Events::Player::Input::KeyDown::D");
		mRigidBody.ApplyForceX(50);
	}
	else if (controller.MoveLeft( ))
	{
		Logger::Debug(LogType::Warning,
					  "GameState::Events::Player::Input::KeyDown::A");
		mRigidBody.ApplyForceX(-50);
	}
	else { mRigidBody.UnsetForceX( ); }

	// if (controller.WasKeyPressed(SDL_SCANCODE_D))
	// {
	// 	Logger::Debug(LogType::Warning,
	// 				  "PRESSED GameState::Events::Player::Input::KeyDown::D");
	// }

	// if (controller.WasKeyReleased(SDL_SCANCODE_D))
	// {
	// 	Logger::Debug(LogType::Warning,
	// 				  "RELEASED GameState::Events::Player::Input::KeyDown::D");
	// }

	// if (controller.IsKeyHeld(SDL_SCANCODE_D))
	// {
	// 	Logger::Debug(LogType::Warning,
	// 				  "HOLDING "
	// 				  "GameState::Events::Player::Input::KeyDown::D");
	// }

	//
	// -------------------------------------------------
	// -------------------------------------------------
	//
	// switch (event.type)
	// {
	// 	// case SDL_PRESSED:
	// 	case SDL_KEYDOWN:
	// 		if (event.key.keysym.sym == SDLK_d)
	// 		{
	// 			Logger::Debug(LogType::Log,
	// 						  "GameState::Events::Player::Input::KeyDown::d");
	// 		}
	// 		else if (event.key.keysym.sym == SDLK_a)
	// 		{
	// 			Logger::Debug(LogType::Log,
	// 						  "GameState::Events::Player::Input::KeyDown::a");
	// 			mRigidBody.ApplyForceX(-50);
	// 		}
	// 		break;

	// 	case SDL_KEYUP:
	// 		if (event.key.keysym.sym == SDLK_d ||
	// 			event.key.keysym.sym == SDLK_a)
	// 		{
	// 			Logger::Debug(
	// 				LogType::Log,
	// 				"++++++++++++++++GameState::Events::Player::UnsetX");
	// 			mRigidBody.UnsetForceX( );
	// 		}
	// 		break;

	// 		//
	// 		// if (event.key.keysym.sym == SDLK_w)
	// 		// {
	// 		// 	std::cout << "\nGameState::Events::Input::w";
	// 		// }
	// 		// else if (event.key.keysym.sym == SDLK_s)
	// 		// {
	// 		// 	std::cout << "\nGameState::Events::Input::s";
	// 		// }
	// 		// else
	// 		// {
	// 		// 	std::cout << "\nGameState::Events::UnsetY";
	// 		// 	velocity.UnsetForceY( );
	// 		// }
	// }
}
