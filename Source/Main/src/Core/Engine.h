#ifndef ENGINE_H
#define ENGINE_H

// #include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// #include "../States/GameStateManager.h"

#include "./Time.h"

#include <fmt/color.h>

class GameStateManager;

class Engine
{
  public:
	Engine( );
	~Engine( );

	SDL_Window* GetWindow( ) const { return mWindow; }
	SDL_Renderer* GetRender( ) const { return mRender; }

  private:
	bool Init( );
	void Loop( );
	// void Events( );

	bool mIsRunning { };
	std::unique_ptr<GameStateManager> mGSM;
	Cris::Time mTime;

	// std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> mWindow;
	// std::unique_ptr<SDL_Renderer> mRender;
	SDL_Window* mWindow;
	SDL_Renderer* mRender;

	int mWindowH;
	int mWindowW;
};

#endif	 // ENGINE_H
