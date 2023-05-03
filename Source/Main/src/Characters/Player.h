#ifndef PLAYER_H
#define PLAYER_H

#include "./Character.h"

class TextureManager;
class Player : public Character
{
  public:
	Player(Node* node, TextureManager& tm);
	~Player( ) override;

	void Update(const float& deltaTime) override;
	void Render( ) override;
	void Events(Controller& controller) override;

	void SetSprite(SDL_Texture* texture) override;

  private:
	RigidBody mRigidBody { this, "RigidBody::Player" };
};

#endif	 // PLAYER_H
