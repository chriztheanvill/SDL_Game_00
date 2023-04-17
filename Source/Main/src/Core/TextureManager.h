#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>

#include "../Core/Node.h"

class TextureManager : public Node
{
  public:
	TextureManager(Node* parent = nullptr);
	~TextureManager( );

	SDL_Texture* Load(std::string_view name = "", std::string_view path = "");

	SDL_Texture* GetTexture(std::string_view name = "");

	void SetRender(SDL_Renderer& render) { mRender = &render; }
	SDL_Renderer* GetRender( ) const { return mRender; }

  protected:
  private:
	std::map<std::string_view, SDL_Texture*> mTextures;
	SDL_Renderer* mRender;
};

#endif	 // TEXTUREMANAGER_H
