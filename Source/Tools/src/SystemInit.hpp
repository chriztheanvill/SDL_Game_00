#ifndef SYSTEMINIT_HPP
#define SYSTEMINIT_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fmt/color.h>

class SystemInit
{
  public:
	SystemInit( );
	~SystemInit( );

	auto SetTexture(std::string_view name = "", std::string_view path = "")
		-> void;
	auto SaveTexture(std::string_view path = "") -> void;

  private:
	auto Init( ) -> void;

	SDL_Window* mWindow;
	SDL_Renderer* mRender;
	SDL_Texture* mTexture;

	int mWindowH;
	int mWindowW;

	std::string path = "assets/Cropped";
};

#endif	 // SYSTEMINIT_HPP
