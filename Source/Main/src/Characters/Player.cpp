#include "Player.h"

Player::Player(TextureManager& tm)
	: Character("Player")
{
	Logger::Debug(LogType::Log, "Player::Constructor: ", GetName( ));

	mPlayerStats = CharStats { 0, 0, 0, 0, 0, 0, 100, 250, 350 };

	SetPosition(Vector2D::Zero( ));
	SetSize({ 50, 50 });
	SetScale({ 1, 1 });
	SetRotation(0.0);

	Collision( ) = {
		static_cast<int>(Position( ).GetX( )),
		static_cast<int>(Position( ).GetY( )),
		static_cast<int>(Size( ).GetX( )),
		static_cast<int>(Size( ).GetY( )),
	};

	mSpriteName = "Player";
	mSpritePath = "assets/tilemaps/Space/PNG/playerShip1_blue.png";

	GetSprite( ).SetName("Sprite::Player");
	GetSprite( ).SetRenderer(tm.GetRender( ));
	GetSprite( ).SetTexture(tm.Load(mSpriteName, mSpritePath));
	GetSprite( ).SetSrc({ });
	GetSprite( ).SetDst({ static_cast<int>(Position( ).GetX( )),
						  static_cast<int>(Position( ).GetY( )),
						  static_cast<int>(Size( ).GetX( )),
						  static_cast<int>(Size( ).GetY( )) });

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
				  "Player::Update::mPlayer::Pos",
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
	Logger::Debug(LogType::Debug, "Player::Render");
	GetSprite( ).Render( );
}

void Player::Events(Controller& controller)
{
	Logger::Debug(LogType::Debug, "Player::Events");

	auto moveX =
		(controller.MoveRight( ) - controller.MoveLeft( )) * mPlayerStats.Speed;
	auto moveY =
		(controller.MoveDown( ) - controller.MoveUp( )) * mPlayerStats.Speed;

	// mRigidBody.ApplyForce({ moveX, moveY });
	mRigidBody.ApplyForceX(moveX);
	mRigidBody.ApplyForceY(moveY);
}
