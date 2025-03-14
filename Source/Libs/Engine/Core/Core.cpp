//
// Created by cris on 12/22/24.
//

#include "Core.hpp"

void CheckCPPVersion() {
  std::cout << "\n\n Check C++ version: ";
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

Core::Core() {
  // Logger::CanWrite(true);
  // Logger::ANewFile( );
  Logger::Debug(LogType::Log, "--- Engine ---");

  CheckCPPVersion();
}

Core::~Core() {
  // 	// NOTE (Obsolete)
  // 	// delete mEngine;
  //
  // 	// mEngine = nullptr;

  //
  // SDL_FreeSurface(m_imgIconSurface);

  // SDL System
  SDL_DestroyRenderer(m_render);
  SDL_DestroyWindow(m_window);

  TTF_Quit();
  IMG_Quit();
  Mix_Quit();
  SDL_Quit();
  Logger::Debug(LogType::Log, "--- ~Engine ---");
}

auto Core::Init() -> bool {
  /* #################### Init SDL2 #################### */
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    Logger::Debug(LogType::Error, "--- Error!!! SDL_INIT_EVERYTHING --- ", SDL_GetError());
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
    // 		   "--- Error!!! SDL_INIT_EVERYTHING --- {}",
    // 		   SDL_GetError( ));
    return false;
  }

  /* Init Image */
  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int initted = IMG_Init(flags);
  if ((initted & flags) != flags) {
    Logger::Debug(LogType::Error, "--- Error!!! IMG_INIT PNG | JPG --- ", IMG_GetError());
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
    // 		   "--- Error!!! IMG_INIT PNG | JPG --- {}",
    // 		   IMG_GetError( ));
    return false;
  }

  if (TTF_Init() != 0) {
    Logger::Debug(LogType::Error, "--- Error!!! TTF_Init --- ", TTF_GetError());
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
    // 		   "--- Error!!! TTF_Init --- {}",
    // 		   TTF_GetError( ));
    return false;
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    Logger::Debug(LogType::Error, "--- Error!!! Music Mixer --- ", Mix_GetError());
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

auto Core::InitGraphics(bool isVSync) -> bool {
  // SDL_DisplayMode displayMode;
  // SDL_GetCurrentDisplayMode(0, &displayMode);
  // m_windowH = displayMode.h;
  // m_windowW = displayMode.w;

  // fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
  // 		   "--- Display size --- H: {} x  w:{}\n\n",
  // 		   m_windowH,
  // 		   m_windowW);
  //

  // ==================================================
  // ==================================================
  // Imgui
  //
  // Setup SDL window
  // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100 (WebGL 1.0)
  m_glsl_version = "#version 100";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
  // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
  m_glsl_version = "#version 300 es";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(__APPLE__)
  // GL 3.2 Core + GLSL 150
  m_glsl_version = "#version 150";
  SDL_GL_SetAttribute(
    SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG
  ); // Always required on Mac
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
  // GL 3.0 + GLSL 130
  m_glsl_version = "#version 330";
  // m_glsl_version = "#version 130";
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

  // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
  SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  // Imgui
  // ==================================================
  // ==================================================

  m_window = SDL_CreateWindow(
    "SDL Pikuma",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    800, // Colocar m_windowH, crea un FAKE full screen size
    600,
    // SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI
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
    Logger::Debug(LogType::Error, "--- Error!!! Create Window --- ", SDL_GetError());
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
    // 		   "--- Error!!! Create Window --- {}",
    // 		   SDL_GetError( ));
    return false;
  }
  Logger::Debug(LogType::Log, "--- Success New Window --- ");

  m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
  // m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED |
  // SDL_RENDERER_PRESENTVSYNC);
  //
  if (!m_render) {
    Logger::Debug(LogType::Error, "--- Error!!! Create Render --- ", SDL_GetError());
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
    // 		   "--- Error!!! Create Render --- {}",
    // 		   SDL_GetError( ));
    return false;
  }

  // ==========================================================
  // ==========================================================
  // Imgui

  m_context = SDL_GL_CreateContext(m_window);

  if (m_context == nullptr) {
    Logger::Debug(LogType::Error, "--- Error: SDL_GL_CreateContext() --- ", SDL_GetError());
    return false;
  }

  SDL_GL_MakeCurrent(m_window, m_context);
  SDL_GL_SetSwapInterval(1); // Enable vsync

  // Imgui
  // ==================================================
  // ==================================================

  // SDL_RenderSetVSync(m_render, isVSync);

  // Make Real fullscreen
  // SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN);

  // m_imgIconSurface = IMG_Load("assets/images/icon.png");
  //
  // SDL_SetWindowIcon(m_window, m_imgIconSurface);

  Logger::Debug(LogType::Log, "--- Success New Render --- ");

  return true;
}