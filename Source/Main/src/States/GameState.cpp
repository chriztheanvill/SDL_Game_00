#include "GameState.h"

#include "GameStateManager.h"
#include "../Core/Engine.h"

#include <iostream>

GameState::GameState(GameStateManager& gsm)
	: State(gsm, "GameState")
	, mPlayer(std::make_unique<Player>(this, gsm))
// , mPlayer(this, gsm)
// , Node(nullptr, "GameState")
{
	// Setting NODE
	SetName("GameState");
	// SetChild(&mPlayer);

	// TextureManager tm(this);
	// tm.SetName("TextureManager GameState Simple");
	// tm.SetRender(GetGameStateManager( ).GetRender( ));
	// GetGameStateManager( ).GetTextureManager( ) = tm;

	// *GetGameStateManager( ).GetTextureManager( ) =
	// 	static_cast<TextureManager&&>(tm);	 // unique_ptr

	//
	// std::unique_ptr<TextureManager> tm =
	// std::make_unique<TextureManager>(this);
	TextureManager* tm = new TextureManager(this);

	tm->SetName("TextureManager GameState Unique_ptr");
	tm->SetRender(GetGameStateManager( ).GetRender( ));
	GetGameStateManager( ).GetTextureManager( ) = *tm;
	// GetGameStateManager( ).GetTextureManager( ) = *tm.release( ); // Unique

	std::cout << "\n\n ### GameState::Constructor : " << GetName( )
			  << " : ### \n";

	Load( );
}

GameState::~GameState( )
{
	//
	std::cout << "\n\n~GameState::Destructor : " << GetName( ) << " :";
	// NodeLogComplete( );
}

void GameState::Load( )
{
	// GetGameStateManager( ).GetTextureManager( )->Load(
	GetGameStateManager( ).GetTextureManager( ).Load(
		"test",
		"assets/images/bkBlue.png");

	mPlayer->SetSprite("Vivian", "assets/images/Vivian.jpg");
	// mPlayer.SetSprite("Vivian", "assets/images/Vivian.jpg");
}

// State* GameState::Update(const float& deltaTime)
std::unique_ptr<State> GameState::Update(const float& deltaTime)
// std::shared_ptr<State> GameState::Update(const float& deltaTime)
{
	std::cout << "\nGameState::Update";

	mPlayer->Update(deltaTime);
	// mPlayer.Update(deltaTime);

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
	mPlayer->Render( );
	// mPlayer.Render( );
}

void GameState::Events(SDL_Event& event)
{
	std::cout << "\nGameState::Events";
	// mPlayer.Events(event);
}

void GameState::EnterState( )
{
	std::cout
		<< "\n==================GameState::EnterState==================\n\n";
}

void GameState::ExitState( )
{
	std::cout
		<< "\n==================GameState::ExitState==================\n\n";
}
