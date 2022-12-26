#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <iostream>

#include <SDL2/SDL_image.h>

class Engine;

class TextureManager
{
  public:
	TextureManager(Engine& engine);
	~TextureManager( );

	SDL_Texture* Load(const std::string& name = "",
					  const std::string& path = "");
	SDL_Texture* GetTexture(const std::string& name = "");

  private:
	std::map<const std::string, SDL_Texture*> mTextures;
	Engine& mEngine;
};

#endif	 // TEXTUREMANAGER_H
