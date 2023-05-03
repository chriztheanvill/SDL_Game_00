#include "Level.h"

Level::Level(LevelManager& lm, TextureManager& tm, std::string_view name)
	: mLevelManager(lm)
	, mPlayer(nullptr, tm)
	, mTextureManager(tm)
	, mName(name)
{
	Logger::Debug(LogType::Log, "--- GameState::Level::Constructor ---");

	Init( );
}

Level::~Level( ) {}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

void Level::Init( )
{
	//
	Logger::Debug(LogType::Log, "--- Level::Init ---");
	Logger::Debug(LogType::Debug, "Loading map: ", mName);
	mRunning = true;
}

void Level::Update(const float& deltaTime)
{
	//
	Logger::Debug(LogType::Debug, "Updating map: ", mName);
	mPlayer.Update(deltaTime);
}

void Level::Render( )
{
	//
	Logger::Debug(LogType::Debug, "Rendering map: ", mName);
	mPlayer.Render( );
}

void Level::Events(Controller& controller)
{
	//
	Logger::Debug(LogType::Debug, "Events map: ", mName);
	mPlayer.Events(controller);
	// mPlayer.Events(event);
}
