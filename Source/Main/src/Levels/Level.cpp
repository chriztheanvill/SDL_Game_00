#include "Level.h"
#include "./LevelManager.hpp"
#include "../ECS/ECS.hpp"

Level::Level(LevelManager& lm, TextureManager& tm, std::string_view name)
	: mLevelManager(lm)
	, mPlayer(tm)
	, mTextureManager(tm)
	, Node(name)
{
	Logger::Debug(LogType::Log, "Level::Constructor: ", GetName( ));

	Init( );
}

Level::~Level( )
{
	Logger::Debug(LogType::Log, "Level::Destructor: ", GetName( ));
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

void Level::Init( )
{
	//
	Logger::Debug(LogType::Log, "Level::Init: ", GetName( ));
	mRegistry = std::make_unique<Registry>( );

	Entity tank = mRegistry->NewEntity("tank");
	Entity truck = mRegistry->NewEntity("truck");

	mRunning = true;
}

void Level::Update(const float& deltaTime)
{
	//
	Logger::Debug(LogType::Debug, "Level::Update:: map: ", GetName( ));
	mPlayer.Update(deltaTime);
}

void Level::Render( )
{
	//
	Logger::Debug(LogType::Debug, "Level::Render map: ", GetName( ));
	mPlayer.Render( );
}

void Level::Events(Controller& controller)
{
	//
	Logger::Debug(LogType::Debug, "Level::Events  ", GetName( ));
	mPlayer.Events(controller);
	// mPlayer.Events(event);
}
