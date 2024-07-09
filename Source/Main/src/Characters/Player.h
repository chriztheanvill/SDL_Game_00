#ifndef PLAYER_H
#define PLAYER_H

#include "./Character.h"

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
	RigidBodyComponent mRigidBody { 2 };

	CharStats mPlayerStats;

	// Test
	// std::string_view mSpriteName = "Player";
	// std::string_view mSpritePath = "assets/images/Vivian.jpg";
};

#endif	 // PLAYER_H
