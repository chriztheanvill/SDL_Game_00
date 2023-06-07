#ifndef ENGINE_H
#define ENGINE_H

// #include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "../States/Engine/GameStateManager.h"

#include "./Time.h"
#include "../Utils/Logger.h"

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

	Cris::Time mTime;

	SDL_Window* mWindow;
	SDL_Renderer* mRender;

	int mWindowH;
	int mWindowW;
};

#endif	 // ENGINE_H
