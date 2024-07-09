#include "Player.h"

Player::Player(TextureManager& tm)
	: Character("Player")
{
	Logger::Debug(LogType::Log, "Player::Constructor: ", GetName( ));

	mPlayerStats = CharStats { 0, 0, 0, 0, 0, 0, 100, 250, 350 };

	SetPosition(Vector2D::Zero( ));
	SetScale({ 1, 1 });
	SetRotation(0.0);

	Collision( ) = {
		static_cast<int>(Position( ).x),
		static_cast<int>(Position( ).y),
		static_cast<int>(Scale( ).x),
		static_cast<int>(Scale( ).y),
	};

	mSpriteName = "Player";
	mSpritePath = "assets/tilemaps/Space/PNG/playerShip1_blue.png";

	GetSprite( ).SetName("Sprite::Player");
	GetSprite( ).SetRenderer(tm.GetRender( ));
	GetSprite( ).SetTexture(tm.AddTexture(mSpriteName, mSpritePath));
	GetSprite( ).SetSrc({ });
	GetSprite( ).SetDst({ static_cast<int>(Position( ).x),
						  static_cast<int>(Position( ).y),
						  static_cast<int>(Scale( ).x),
						  static_cast<int>(Scale( ).y) });

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

void Player::SetSprite(SDL_Texture* texture) { GetSprite( ).SetTexture(texture); }

void Player::Update(const float& deltaTime)
{
	mRigidBody.Update(deltaTime);
	// mRigidBody.ApplyForceY(mGravity);
	Position( ).Transform(mRigidBody.Velocity( ));

	// Logger::Debug(LogType::Debug,
	// 			  "++++++++++++++++++Player::RigidBody++++++++++++++++++");

	// Logger::Debug(LogType::Debug,
	// 			  "Player::RigidBody::Force",
	// 			  " x: "sv,
	// 			  mRigidBody.Force( ).x,
	// 			  " - y: "sv,
	// 			  mRigidBody.Force( ).y);

	// Logger::Debug(LogType::Debug,
	// 			  "Player::RigidBody::Acceleration",
	// 			  " x: "sv,
	// 			  mRigidBody.Acceleration( ).x,
	// 			  " - y: "sv,
	// 			  mRigidBody.Acceleration( ).y);

	// Logger::Debug(LogType::Debug,
	// 			  "-------------Player::RigidBody-------------");

	Logger::Debug(
	  LogType::Debug,
	  "Player::Update::mPlayer::Pos",
	  " x: "sv,
	  Position( ).x,
	  " - y: "sv,
	  Position( ).y
	);

	Collision( ) = {
		static_cast<int>(Position( ).x),
		static_cast<int>(Position( ).y),
		static_cast<int>(Scale( ).x),
		static_cast<int>(Scale( ).y),
	};

	GetSprite( ).SetDst({ static_cast<int>(Position( ).x),
						  static_cast<int>(Position( ).y),
						  static_cast<int>(Scale( ).x),
						  static_cast<int>(Scale( ).y) });
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

	auto moveX = (controller.MoveRight( ) - controller.MoveLeft( )) * mPlayerStats.Speed;
	auto moveY = (controller.MoveDown( ) - controller.MoveUp( )) * mPlayerStats.Speed;

	// mRigidBody.ApplyForce({ moveX, moveY });
	mRigidBody.ApplyForceX(moveX);
	mRigidBody.ApplyForceY(moveY);
}
