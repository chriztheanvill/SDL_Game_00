#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_image.h>

#include <string>
#include <string_view>

#include "../Core/Node.h"

class Graphics : public Node
{
  public:
	Graphics( );
	~Graphics( ) override;

	void SetRender(SDL_Renderer* render) { mRender = render; }
	// void SetWindow(SDL_Window* window) { mWindow = window; }

	// SDL_Window* GetWindow( ) const { return mWindow; }
	SDL_Renderer* GetRender( ) const { return mRender; }

  protected:
	SDL_Renderer* mRender;

  private:
	// std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> mWindow;
	// std::unique_ptr<SDL_Renderer> mRender;
	// SDL_Window* mWindow;
};

#endif	 // GRAPHICS_H
