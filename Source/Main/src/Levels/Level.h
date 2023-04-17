#ifndef LEVEL_H
#define LEVEL_H

// Maps

#include "../Characters/Player.h"

class TextureManager;

class Level
{
  public:
	Level(TextureManager& tm);
	~Level( );

	void Update(const float& deltaTime);
	void Render( );
	void Events(SDL_Event& event);

	void SetTextureManager(TextureManager* tm) { mTextureManager = tm; }

	void Init( );

  private:
	TextureManager* mTextureManager;
	Player mPlayer;
};

#endif	 // LEVEL_H
