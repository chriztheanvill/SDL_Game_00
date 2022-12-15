#include "Engine.h"
#include <fmt/color.h>

Engine::Engine( )
	: mGSM(std::make_unique<GameStateManager>(*this))
{
	Init( );
	Loop( );
}

Engine::~Engine( )
{
	SDL_DestroyRenderer(mRender);
	SDL_DestroyWindow(mWindow);

	TTF_Quit( );
	IMG_Quit( );
	Mix_Quit( );
	SDL_Quit( );
}

void Engine::Init( )
{
	/* Init Everything */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! SDL_INIT_EVERYTHING --- {}",
				   SDL_GetError( ));
		exit(1);
	}

	/* Init Image */
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! IMG_INIT PNG | JPG --- {}",
				   IMG_GetError( ));
		exit(1);
	}

	if (TTF_Init( ) != 0)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! TTF_Init --- {}",
				   TTF_GetError( ));
		exit(1);
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
				   "--- Error!!! Music Mixer --- {}",
				   Mix_GetError( ));
		exit(1);
	}

	/* ------------------------------------------------------------------- */
	fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
			   "+++ Success all libs!!! +++\n");
	// Turn ON the game

	mWindow = SDL_CreateWindow("SDL Pikuma",
							   SDL_WINDOWPOS_CENTERED,
							   SDL_WINDOWPOS_CENTERED,
							   800,
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
		exit(1);
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
		exit(1);
	}

	// mIsRunning = true;
	mGSM->SetIsRunning(true);
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

void Engine::Events( )
{
	// SDL_Event event { };
	// while (SDL_PollEvent(&event))
	// {
	// 	/* ======== SYSTEM ======== */
	// 	switch (event.type)
	// 	{
	// 		case SDL_QUIT: mIsRunning = false; break;
	// 		case SDL_KEYDOWN:
	// 			if (event.key.keysym.sym == SDLK_q ||
	// 				event.key.keysym.sym == SDLK_ESCAPE)
	// 			{
	// 				mIsRunning = false;
	// 				// std::cout << "\n\nQuitting game by Q.\n";
	// 				fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
	// 						   "--- Quitting game with Q --- ");
	// 			}
	// 	}
	// 	/* ======== ~SYSTEM ======== */

	// 	// 	/* ======== Game ======== */
	// 	// 	// mCurrent->Events(event);
	// 	// 	/* ======== ~Game ======== */
	// }
}