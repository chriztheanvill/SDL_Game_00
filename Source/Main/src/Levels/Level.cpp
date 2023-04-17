#include "Level.h"
#include "../Core/TextureManager.h"

Level::Level(TextureManager& tm)
	: mTextureManager(&tm)
	, mPlayer(nullptr, tm)
{
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

	// mPlayer.SetSpriteRenderer(mTextureManager->GetRender( ));
	// mPlayer.SetSprite(
	// 	mTextureManager->Load("Vivian", "assets/images/Vivian.jpg"));
}

void Level::Update(const float& deltaTime)
{
	//
	mPlayer.Update(deltaTime);
}

void Level::Render( )
{
	//
	mPlayer.Render( );
}

void Level::Events(SDL_Event& event)
{
	//
}
