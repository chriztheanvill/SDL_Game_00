#include "Sprite.h"

#include <cassert>

Sprite::Sprite( ) {}

Sprite::~Sprite( ) {}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

void Sprite::Update(const float& deltatime) {}

void Sprite::Render( )
{
	// A rectangle
	// SDL_SetRenderDrawColor(mRender, 255, 255, 255, 255);
	// SDL_RenderFillRect(mRender, &mDst);

	// The sprite
	if (mSrc.h == 0 && mSrc.w == 0 && mSrc.x == 0 && mSrc.y == 0)
	{
		SDL_RenderCopy(mRender, mTexture, nullptr, &mDst);
	}
	else { SDL_RenderCopy(mRender, mTexture, &mSrc, &mDst); }
}