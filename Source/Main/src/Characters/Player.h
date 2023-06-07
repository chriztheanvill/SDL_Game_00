#ifndef PLAYER_H
#define PLAYER_H

#include "./Character.h"

class TextureManager;
class Player : public Character
{
  public:
	Player(TextureManager& tm);
	~Player( ) override;

	void Update(const float& deltaTime) override;
	void Render( ) override;
	void Events(Controller& controller) override;

	void SetSprite(SDL_Texture* texture) override;

  private:
	RigidBody mRigidBody { };
	TransformComponent tc { };

	const uint8_t mSpeed { 200 };
	const uint8_t mGravity { 250 };
	const uint16_t mJump { 350 };
};

#endif	 // PLAYER_H
