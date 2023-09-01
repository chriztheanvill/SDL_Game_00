#ifndef LEVEL_H
#define LEVEL_H

// Maps
#include "../Graphics/TextureManager.h"
#include "../Characters/Player.h"

class LevelManager;
class Controller;
class Registry;

#include "../Core/Node.h"
class Level : public Node
{
  public:
	Level(LevelManager& lm,
		  TextureManager& tm,
		  std::string_view name = "LevelEmpty");
	~Level( ) override;

	void Update(const float& deltaTime);
	void Render( );
	void Events(Controller& controller);

	void SetTextureManager(TextureManager& tm) { mTextureManager = tm; }

	void Init( );

	[[nodiscard]] auto IsRunning( ) const -> bool { return mRunning; }

  private:
	bool mRunning { };
	bool mInit { };
	bool mFinish { };

	Player mPlayer;
	TextureManager& mTextureManager;
	LevelManager& mLevelManager;

	std::unique_ptr<Registry> mRegistry;
};

#endif	 // LEVEL_H
