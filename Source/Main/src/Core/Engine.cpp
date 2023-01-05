#include "Engine.h"
#include <fmt/color.h>
#include "../States/GameStateManager.h"
// #include "./Time.h"

void CheckCPPVersion( )
{
	std::cout << "Check C++ version: ";
	if (__cplusplus == 202002L) { std::cout << "C++20\n"; }
	else if (__cplusplus == 201703L) { std::cout << "C++17\n"; }
	else if (__cplusplus == 201402L) { std::cout << "C++14\n"; }
	else if (__cplusplus == 201103L) { std::cout << "C++11\n"; }
	else if (__cplusplus == 199711L) { std::cout << "C++98\n"; }
	else { std::cout << "pre-standard C++\n"; }
}

Engine::Engine( )
{
	CheckCPPVersion( );
	if (!Init( )) return;	// Init only SDL2 libs

	mGSM = std::make_unique<GameStateManager>(*mRender);
	// mGSM = std::make_unique<GameStateManager>(*this);
	// mGSM->SetIsRunning(true);

	Loop( );
}

Engine::~Engine( )
{
	mGSM = nullptr;

	// SDL System
	SDL_DestroyRenderer(mRender);
	SDL_DestroyWindow(mWindow);

	TTF_Quit( );
	IMG_Quit( );
	Mix_Quit( );
	SDL_Quit( );
}

bool Engine::Init( )
{
	/* #################### Init SDL2 #################### */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! SDL_INIT_EVERYTHING --- {}",
				   SDL_GetError( ));
		return false;
	}

	/* Init Image */
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! IMG_INIT PNG | JPG --- {}",
				   IMG_GetError( ));
		return false;
	}

	if (TTF_Init( ) != 0)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! TTF_Init --- {}",
				   TTF_GetError( ));
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! Music Mixer --- {}",
				   Mix_GetError( ));
		return false;
	}

	/* ------------------------------------------------------------------- */
	fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
			   "\n\n+++ Success all libs!!! +++\n");
	// Turn ON the game

	// SDL_DisplayMode displayMode;
	// SDL_GetCurrentDisplayMode(0, &displayMode);
	// mWindowH = displayMode.h;
	// mWindowW = displayMode.w;

	// fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
	// 		   "--- Display size --- H: {} x  w:{}\n\n",
	// 		   mWindowH,
	// 		   mWindowW);

	mWindow = SDL_CreateWindow(
		"SDL Pikuma",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,   // Colocar mWindowH, crea un FAKE full screen size
		600,
		SDL_WINDOW_OPENGL);
	// mWindow.reset(SDL_CreateWindow("SDL Pikuma",
	// 							   SDL_WINDOWPOS_CENTERED,
	// 							   SDL_WINDOWPOS_CENTERED,
	// 							   800,
	// 							   600,
	// 							   SDL_WINDOW_OPENGL));
	// mWindow =
	// 	std::unique_ptr<SDL_Window>(SDL_CreateWindow("SDL Pikuma",
	// 												 SDL_WINDOWPOS_CENTERED,
	// 												 SDL_WINDOWPOS_CENTERED,
	// 												 800,
	// 												 600,
	// 												 SDL_WINDOW_OPENGL));

	if (!mWindow)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! Create Window --- {}",
				   SDL_GetError( ));
		return false;
	}

	mRender = SDL_CreateRenderer(mWindow,
								 -1,
								 SDL_RENDERER_ACCELERATED |
									 SDL_RENDERER_PRESENTVSYNC);
	// mRender.reset(
	// 	SDL_CreateRenderer(mWindow.get( ), -1, SDL_RENDERER_ACCELERATED));
	// mRender = std::unique_ptr<SDL_Renderer>(
	// 	SDL_CreateRenderer(mWindow.get( ), -1, SDL_RENDERER_ACCELERATED));
	if (!mRender)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! Create Render --- {}",
				   SDL_GetError( ));
		return false;
	}

	// Make Real fullscreen
	// SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);

	/* #################### Init SDL2 #################### */
	return true;
}

void Engine::Loop( )
{
	while (mGSM->GetIsRunning( ))
	{
		// fmt::print("\nEngine::Loop deltaTime: {}", mTime.GetDeltaTime( ));
		mTime.Tick( );
		mGSM->Update(mTime.GetDeltaTime( ));
	}
	// mGSM->Update(0);
}
