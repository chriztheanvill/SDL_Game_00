#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SDL2/SDL_image.h>

#include <string>
#include <map>

class TextureManager
{
  private:
	std::map<std::string, SDL_Texture*> m_textures;
	SDL_Renderer* m_render { };

  public:
	TextureManager( );
	// TextureManager(const TextureManager& other);			  // Copy
	// TextureManager& operator=(const TextureManager& other);	  // Copy Operator
	virtual ~TextureManager( );

	SDL_Texture* AddTexture(const std::string& name = "", const std::string& path = "");
	SDL_Texture* GetTexture(const std::string& name = "") const;

	void SetRender(SDL_Renderer& render) { m_render = &render; }
	SDL_Renderer* GetRender( ) const { return m_render; }

	auto Render(const SDL_Rect& src, const SDL_Rect& dst, const std::string& name) -> void;
	auto Clear( ) -> void;
};

#endif	 // TEXTUREMANAGER_HPP
