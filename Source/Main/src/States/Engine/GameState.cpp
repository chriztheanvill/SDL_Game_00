#include "GameState.h"

#include "GameStateManager.h"

#include "../../Graphics/TextureManager.h"
#include "../../Core/Engine.h"
#include "../../Levels/Level.h"

#include <iostream>

GameState::GameState(GameStateManager& gsm, TextureManager& tm)
	: EngineState("GameState", gsm, tm)
	, mLevelManager(tm)
{
	// Setting NODE
	// SetName("GameState");
	// SetChild(&mPlayer);

	Logger::Debug(LogType::Log, "### GameState::Constructor :", GetName( ));

	Load( );
}

GameState::~GameState( )
{
	//
	Logger::Debug(LogType::Log, "### ~GameState::Destructor :", GetName( ));
	// NodeLogComplete( );
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

void GameState::Load( )
{
	// ---------------------------------------------------------------
	// Texture Manager
	// Crear un nuevo Texture Manager, NO se si sea buena idea.
	// Solo probando
	Logger::Debug(LogType::Debug, "GameState::Load");

	TextureManager tm;
	tm.SetName("TextureManager GameState Simple");
	tm.SetRender(*GetTextureManager( ).GetRender( ));
	// GetTextureManager( ) = nullptr;	  // Just calling the Destructor
	GetTextureManager( ) = tm;

	// *GetGameStateManager( ).GetTextureManager( ) =
	// 	static_cast<TextureManager&&>(tm);	 // unique_ptr

	//
	// std::unique_ptr<TextureManager> tm =
	// std::make_unique<TextureManager>(this);

	// TextureManager* tm = new TextureManager;

	// tm->SetName("TextureManager GameState Unique_ptr");
	// tm->SetRender(GetGameStateManager( ).GetRender( ));
	// GetGameStateManager( ).GetTextureManager( ) = *tm;
	// GetGameStateManager( ).GetTextureManager( ) = *tm.release( ); // Unique

	GetTextureManager( ).Load("test", "assets/images/bkBlue.png");	 // Test

	// ---------------------------------------------------------------
	// Levels
	// mLevel00.SetTextureManager(&GetTextureManager( ));
	// mLevel00.Init( );
}

std::unique_ptr<EngineState> GameState::Update(const float& deltaTime)
{
	Logger::Debug(LogType::Debug, "GameState::Update");

	mLevelManager.Update(deltaTime);

	// return this;
	// if (GetGSM( ).GetMenuState( ))
	// {
	// 	std::cout << "\nGameState::Update::Return mMenuState;";
	// 	return GetGSM( ).GetMenuState( );
	// }
	return nullptr;
}

void GameState::Render( )
{
	//
	mLevelManager.Render( );
}

void GameState::Events(Controller& controller)
{
	// Logger::Debug(LogType::Debug, "GameState::Events");
	mLevelManager.Events(controller);
}

void GameState::EnterState( )
{
	Logger::Debug(LogType::Log,
				  "==================GameState::EnterState==================");
	// Load( );
}

void GameState::ExitState( )
{
	Logger::Debug(LogType::Log,
				  "==================GameState::ExitState==================");
}
