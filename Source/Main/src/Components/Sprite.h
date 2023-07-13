#ifndef SPRITE_HPP
#define SPRITE_HPP

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
	[[nodiscard]] auto GetTexture( ) const -> SDL_Texture*
	{
		if (!mTexture)
		{
			SDL_Log("Warning, this sprite, has no texture!!!");
			return nullptr;
		}
		return mTexture;
	}

	void SetName(std::string_view name) { mName = name; }
	void SetPath(std::string_view path) { mPath = path; }

	void SetSrc(const SDL_Rect& rect) { mSrc = rect; }
	auto GetSrc( ) const -> SDL_Rect { return mSrc; }

	void SetDst(const SDL_Rect& rect) { mDst = rect; }
	auto GetDst( ) const -> SDL_Rect { return mDst; }

	void SetPosition(const Vector2D& pos) { mPosition = pos; }
	auto GetPosition( ) const -> Vector2D { return mPosition; }

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

#endif	 // SPRITE_HPP
