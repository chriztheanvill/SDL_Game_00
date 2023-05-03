#ifndef LEVEL_H
#define LEVEL_H

// Maps
#include "./LevelManager.hpp"
#include "../Graphics/TextureManager.h"

class Level
{
  public:
	Level(LevelManager& lm, TextureManager& tm, std::string_view name);
	~Level( );

	void Update(const float& deltaTime);
	void Render( );
	void Events(Controller& controller);

	void SetTextureManager(TextureManager& tm) { mTextureManager = tm; }

	void Init( );

	bool IsRunning( ) const { return mRunning; }

  private:
	bool mRunning { };
	bool mInit { };
	bool mFinish { };

	std::string_view mName;

	Player mPlayer;
	TextureManager& mTextureManager;
	LevelManager& mLevelManager;
};

#endif	 // LEVEL_H
