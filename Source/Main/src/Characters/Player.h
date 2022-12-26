#ifndef PLAYER_H
#define PLAYER_H

#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

#include <SDL2/SDL.h>

class GameStateManager;

class Player
{
  public:
	Player(GameStateManager& gsm);
	~Player( );

	void Update(const float& deltaTime);
	void Render( );
	void Events(SDL_Event& event);

	SDL_Rect& Collision( ) { return mCollision; }
	RigidBody& Body( ) { return mRigidBody; }
	Vector2D& Position( ) { return mPosition; }

  private:
	SDL_Rect mCollision { };
	RigidBody mRigidBody { };
	Vector2D mPosition { };

	SDL_Texture* mPlayerTexture;

	GameStateManager& mGameStateManager;
};

#endif	 // PLAYER_H
