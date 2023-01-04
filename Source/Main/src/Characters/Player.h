#ifndef PLAYER_H
#define PLAYER_H

#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

#include <SDL2/SDL.h>

#include "../Core/Node.h"

class GameStateManager;

class Player : public Node
{
  public:
	Player(Node* node, GameStateManager& gsm);
	~Player( ) override;

	void Update(const float& deltaTime);
	void Render( );
	void Events(SDL_Event& event);

	void SetSprite(const std::string& name, const std::string& path);

	SDL_Rect& Collision( ) { return mCollision; }
	RigidBody& Body( ) { return mRigidBody; }
	Vector2D& Position( ) { return mPosition; }

  private:
	SDL_Rect mCollision { };
	RigidBody mRigidBody;
	Vector2D mPosition { };

	SDL_Texture* mPlayerTexture;

	GameStateManager& mGameStateManager;
};

#endif	 // PLAYER_H
