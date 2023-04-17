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
	void Events(SDL_Event& event) override;

	void SetSprite(SDL_Texture* texture) override;
};

#endif	 // PLAYER_H
