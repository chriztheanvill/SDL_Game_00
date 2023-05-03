#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP

#include <memory>
#include <vector>
#include <map>
#include <string_view>
#include <string>

#include "../Characters/Player.h"
#include "../Graphics/TextureManager.h"

class Level;
class TextureManager;

enum class LevelNames
{
	Lv_00,	 // Debugger
	Lv_01,
	Lv_02,
	Lv_03,
	Lv_04,
};

class LevelManager
{
  public:
	LevelManager(TextureManager& tm);
	~LevelManager( );

	virtual void Update(const float& deltaTime);
	virtual void Render( );
	virtual void Events(Controller& controller);

	TextureManager& GetTextureManager( ) { return mTextureManager; }
	void SetTextureManager(TextureManager& tm) { mTextureManager = tm; }

	virtual void Init( );
	void SetLevel(LevelNames name);

  protected:
	TextureManager& mTextureManager;

  private:
	LevelNames mCurrentLevelName;
	// std::string_view mCurrentLevelName;
	std::map<LevelNames, std::unique_ptr<Level>> mLevels;
	// std::map<std::string_view, std::unique_ptr<Level>> mLevels;
	// std::map<std::unique_ptr<Level>, std::string_view> mLevels;
	std::unique_ptr<Level> mCurrentLevel { };
};

#endif	 // LEVELMANAGER_HPP
