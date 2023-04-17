#ifndef SPRITE_H
#define SPRITE_H

#include "../Physics/Vector2D.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite
{
  public:
	Sprite( );
	~Sprite( );

	void SetRenderer(SDL_Renderer* render) { mRender = render; }
	void SetTexture(SDL_Texture* texture) { mTexture = texture; }
	SDL_Texture* GetTexture( ) const
	{
		if (!mTexture)
		{
			SDL_Log("Warning, this sprite, has no texture!!!");
			return nullptr;
		}
		return mTexture;
	}

	void SetSrc(const SDL_Rect& rect) { mSrc = rect; }
	SDL_Rect GetSrc( ) const { return mSrc; }

	void SetDst(const SDL_Rect& rect) { mDst = rect; }
	SDL_Rect GetDst( ) const { return mDst; }

	void SetPosition(const Vector2D& pos) { mPosition = pos; }
	Vector2D GetPosition( ) const { return mPosition; }

	void Update(const float& deltatime);
	void Render( );

  private:
	std::string_view mName;
	std::string_view mPath;

	SDL_Rect mSrc { };
	SDL_Rect mDst { };
	Vector2D mPosition { };

	SDL_Texture* mTexture;
	SDL_Renderer* mRender;
};

#endif	 // SPRITE_H
