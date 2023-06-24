#include "Player.h"
#include "../Graphics/TextureManager.h"

Player::Player(TextureManager& tm)
	: Character("Player")
{
	Logger::Debug(LogType::Log, "Player::Constructor: ", GetName( ));

	tc.position = Vector2D::Zero( );
	tc.scale = { 100, 200 };
	tc.rotation = 0.0;

	SetTransform(tc);
	// SetTransform({ Vector2D::Zero( ), { 100, 200 }, 0.0 });

	Collision( ) = {
		static_cast<int>(GetTransform( ).position.GetX( )),
		static_cast<int>(GetTransform( ).position.GetY( )),
		static_cast<int>(GetTransform( ).scale.GetX( )),
		static_cast<int>(GetTransform( ).scale.GetY( )),
	};

	GetSprite( ).SetName("Sprite::Player");
	GetSprite( ).SetRenderer(tm.GetRender( ));
	GetSprite( ).SetTexture(tm.Load("Vivian", "assets/images/Vivian.jpg"));
	GetSprite( ).SetSrc({ });
	GetSprite( ).SetDst({ static_cast<int>(GetTransform( ).position.GetX( )),
						  static_cast<int>(GetTransform( ).position.GetY( )),
						  static_cast<int>(GetTransform( ).scale.GetX( )),
						  static_cast<int>(GetTransform( ).scale.GetY( )) });
	// GetSprite( ).SetDst({ 0, 0, 100, 300 });

	// GetSprite( ).SetRenderer(tm->GetRender( ));
	// GetSprite( ).SetTexture(tm->Load("Vivian", "assets/images/Vivian.jpg"));
}

Player::~Player( )
{
	Logger::Debug(LogType::Log, "~Player::Destructor: ", GetName( ));
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
	mRigidBody.Update(GameType::TopDown, deltaTime);
	// mRigidBody.ApplyForceY(mGravity);
	Position( ).Transform(mRigidBody.Velocity( ));

	// Logger::Debug(LogType::Debug,
	// 			  "++++++++++++++++++Player::RigidBody++++++++++++++++++");

	// Logger::Debug(LogType::Debug,
	// 			  "Player::RigidBody::Force",
	// 			  " x: "sv,
	// 			  mRigidBody.Force( ).GetX( ),
	// 			  " - y: "sv,
	// 			  mRigidBody.Force( ).GetY( ));

	// Logger::Debug(LogType::Debug,
	// 			  "Player::RigidBody::Acceleration",
	// 			  " x: "sv,
	// 			  mRigidBody.Acceleration( ).GetX( ),
	// 			  " - y: "sv,
	// 			  mRigidBody.Acceleration( ).GetY( ));

	// Logger::Debug(LogType::Debug,
	// 			  "-------------Player::RigidBody-------------");

	Logger::Debug(LogType::Debug,
				  "Player::Update::mPlayer:",
				  " x: "sv,
				  GetTransform( ).position.GetX( ),
				  " - y: "sv,
				  GetTransform( ).position.GetY( ));

	Collision( ) = {
		static_cast<int>(Position( ).GetX( )),
		static_cast<int>(Position( ).GetY( )),
		static_cast<int>(Scale( ).GetX( )),
		static_cast<int>(Scale( ).GetY( )),
	};

	GetSprite( ).SetDst({ static_cast<int>(Position( ).GetX( )),
						  static_cast<int>(Position( ).GetY( )),
						  static_cast<int>(Scale( ).GetX( )),
						  static_cast<int>(Scale( ).GetY( )) });
}

void Player::Render( )
{
	// SDL_SetRenderDrawColor(mGameStateManager.GetEngine( ).GetRender( ),
	Logger::Debug(LogType::Debug, "Player::Render");
	GetSprite( ).Render( );
}

void Player::Events(Controller& controller)
{
	Logger::Debug(LogType::Debug, "Player::Events");

	if (controller.MoveRight( ))
	{
		Logger::Debug(LogType::Warning, "Player::Input::KeyDown::D");
		mRigidBody.ApplyForceX(mSpeed);
	}
	else if (controller.MoveLeft( ))
	{
		Logger::Debug(LogType::Warning, "Player::Input::KeyDown::A");
		mRigidBody.ApplyForceX(-mSpeed);
	}
	// else { mRigidBody.UnsetForceX( ); } // Platformer
	else if (controller.MoveUp( ))
	{
		Logger::Debug(LogType::Warning, "Player::Input::KeyDown::W");
		mRigidBody.ApplyForceY(-mSpeed);
	}
	else if (controller.MoveDown( ))
	{
		Logger::Debug(LogType::Warning, "Player::Input::KeyDown::S");
		mRigidBody.ApplyForceY(mSpeed);
	}
	else { mRigidBody.UnsetForce( ); }

	// -------------------------------------------------
	// -------------------------------------------------
}
