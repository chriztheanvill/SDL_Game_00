#ifndef ENGINE_H
#define ENGINE_H

// #include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "../States/GameStateManager.h"

#include "./Time.h"
#include <fmt/color.h>

class Engine
{
  public:
	Engine( );
	~Engine( );

  private:
	bool Init( );
	void Loop( );

	bool SDL2( );
	bool InitGraphics( );

	bool mIsRunning { };
	GameStateManager mGSM;
	Cris::Time mTime;

	SDL_Window* mWindow;
	SDL_Renderer* mRender;

	int mWindowH;
	int mWindowW;
};

#endif	 // ENGINE_H
