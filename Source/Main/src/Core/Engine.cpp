#include "Engine.h"
// #include "../States/GameStateManager.h"
// #include "./Time.h"

// bool Logger::write = false;

void CheckCPPVersion( ) {
	std::cout << "\n\nCheck C++ version: ";
	if (__cplusplus == 202002L) {
		std::cout << "C++20\n";
	} else if (__cplusplus == 201703L) {
		std::cout << "C++17\n";
	} else if (__cplusplus == 201402L) {
		std::cout << "C++14\n";
	} else if (__cplusplus == 201103L) {
		std::cout << "C++11\n";
	} else if (__cplusplus == 199711L) {
		std::cout << "C++98\n";
	} else {
		std::cout << "pre-standard C++\n";
	}
}

Engine::Engine( ) {
	// Logger::CanWrite(true);
	// Logger::ANewFile( );
	Logger::Debug(LogType::Log, "--- Engine ---");

	CheckCPPVersion( );
}

Engine::~Engine( ) {
	// 	// NOTE (Obsolete)
	// 	// delete mEngine;
	//
	// 	// mEngine = nullptr;

	// SDL System
	SDL_DestroyRenderer(m_render);
	SDL_DestroyWindow(m_window);

	TTF_Quit( );
	IMG_Quit( );
	Mix_Quit( );
	SDL_Quit( );
	Logger::Debug(LogType::Log, "--- ~Engine ---");
}

auto Engine::Init( ) -> bool {
	/* #################### Init SDL2 #################### */
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Debug(LogType::Error, "--- Error!!! SDL_INIT_EVERYTHING --- ", SDL_GetError( ));
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- Error!!! SDL_INIT_EVERYTHING --- {}",
		// 		   SDL_GetError( ));
		return false;
	}

	/* Init Image */
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		Logger::Debug(LogType::Error, "--- Error!!! IMG_INIT PNG | JPG --- ", IMG_GetError( ));
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- Error!!! IMG_INIT PNG | JPG --- {}",
		// 		   IMG_GetError( ));
		return false;
	}

	if (TTF_Init( ) != 0) {
		Logger::Debug(LogType::Error, "--- Error!!! TTF_Init --- ", TTF_GetError( ));
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- Error!!! TTF_Init --- {}",
		// 		   TTF_GetError( ));
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		Logger::Debug(LogType::Error, "--- Error!!! Music Mixer --- ", Mix_GetError( ));
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- Error!!! Music Mixer --- {}",
		// 		   Mix_GetError( ));
		return false;
	}

	/* ------------------------------------------------------------------- */
	Logger::Debug(LogType::Log, "+++ Success all libs!!! +++");
	// fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
	// 		   "\n\n+++ Success all libs!!! +++\n");
	// Turn ON the game

	/* #################### Init SDL2 #################### */
	return true;
}

auto Engine::InitGraphics( ) -> bool {
	// SDL_DisplayMode displayMode;
	// SDL_GetCurrentDisplayMode(0, &displayMode);
	// m_windowH = displayMode.h;
	// m_windowW = displayMode.w;

	// fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
	// 		   "--- Display size --- H: {} x  w:{}\n\n",
	// 		   m_windowH,
	// 		   m_windowW);

	m_window = SDL_CreateWindow(
	  "SDL Pikuma",
	  SDL_WINDOWPOS_CENTERED,
	  SDL_WINDOWPOS_CENTERED,
	  800,	 // Colocar m_windowH, crea un FAKE full screen size
	  600,
	  SDL_WINDOW_OPENGL
	);
	// m_window.reset(SDL_CreateWindow("SDL Pikuma",
	// 							   SDL_WINDOWPOS_CENTERED,
	// 							   SDL_WINDOWPOS_CENTERED,
	// 							   800,
	// 							   600,
	// 							   SDL_WINDOW_OPENGL));
	// m_window =
	// 	std::unique_ptr<SDL_Window>(SDL_CreateWindow("SDL Pikuma",
	// 												 SDL_WINDOWPOS_CENTERED,
	// 												 SDL_WINDOWPOS_CENTERED,
	// 												 800,
	// 												 600,
	// 												 SDL_WINDOW_OPENGL));

	if (!m_window) {
		Logger::Debug(LogType::Error, "--- Error!!! Create Window --- ", SDL_GetError( ));
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- Error!!! Create Window --- {}",
		// 		   SDL_GetError( ));
		return false;
	}
	Logger::Debug(LogType::Log, "--- Success New Window --- ");

	m_render
	  = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_render) {
		Logger::Debug(LogType::Error, "--- Error!!! Create Render --- ", SDL_GetError( ));
		// fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
		// 		   "--- Error!!! Create Render --- {}",
		// 		   SDL_GetError( ));
		return false;
	}

	// Make Real fullscreen
	// SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

	SDL_SetWindowIcon(m_window, IMG_Load("assets/images/icon.png"));

	Logger::Debug(LogType::Log, "--- Success New Render --- ");

	return true;
}
