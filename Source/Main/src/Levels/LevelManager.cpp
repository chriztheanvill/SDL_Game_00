#include "LevelManager.hpp"
#include "Level.h"

#include <iostream>

LevelManager::LevelManager(TextureManager& tm)
	: mTextureManager(tm)
{
	Logger::Debug(LogType::Log, "LevelManager::Constructor. ");
	Init( );
}

LevelManager::~LevelManager( )
{
	Logger::Debug(LogType::Log, "~LevelManager::Destructor. ");
}

void LevelManager::Init( )
{
	Logger::Debug(LogType::Debug, "LevelManager::Init ");

	mCurrentLevelName = LevelNames::Lv_00;

	// mCurrentLevel = std::make_unique<Level>(*this, mTextureManager,
	// "Level_00");

	mLevels.emplace(
		LevelNames::Lv_00,
		std::make_unique<Level>(*this, mTextureManager, "Level_00"));

	mLevels.emplace(
		LevelNames::Lv_01,
		std::make_unique<Level>(*this, mTextureManager, "Level_01"));

	Logger::Debug(LogType::Warning,
				  "LevelManager::Init Choosing level: ",
				  static_cast<int>(mCurrentLevelName));

	mCurrentLevel = std::move(mLevels[mCurrentLevelName]);

	//
	// for (const auto& [key, var] : mLevels)
	// {
	// 	//
	// 	std::cout << "\nkey: " << key << " - var: " << var;
	// }
}

void LevelManager::SetLevel(LevelNames name) { mCurrentLevelName = name; }

void LevelManager::Update(const float& deltaTime)
{
	mCurrentLevel->Update(deltaTime);
}

void LevelManager::Render( )
{
	//
	mCurrentLevel->Render( );
}

void LevelManager::Events(Controller& controller)
{
	mCurrentLevel->Events(controller);
}
