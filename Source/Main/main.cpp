/**
 * @file main.cpp
 * @author Cristian Nieto (chriztheanvill@gmail.com)
 * @brief A 2D Game Engine, made in C++ Test
 * @date 2022-14-12
 *
 * @copyright Copyright (c) 2021
 *
 */

// // For this, in Cmake on Graphics, enable X11
// // #include <X11/Xlib.h>

// Just for show the icons in VS Code
// NOTE
// DONE
// WARNING
// BUG
// ERR
// ERROR
// DEPRECATED
// FIXME
// FIX
// TODO(cris):

/* NOTE to check the program process:
    # Glances
    ## Simple
    ## glances -612 -t 0.5 -f name:.*program_name*
    ## With left panel
    ## glances -61 -t 0.5 -f name:.*program_name*
    ### Shortcuts:
        q = exit

    # htop
    # htop --filter=program_name
        f10 = exit

    Check address:
    valgrind build/Debug/bin/sdl2_Game_00
*/

// #include <Core/Core.hpp>
#include <Core/Engine.h>
#include <Graphics/TextureManager.h>

#include "src/Game/Game.hpp"

#include "Graphics/TextureManager.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "Input/Controller.h"
#include "imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  /* NOTE: Do not use Singleton
      Engine* e = Engine::GetInstance( );
      e->Init( );
  */

  Logger::Debug(LogType::Check, "Main Init Engine");
  Engine engine;

  Logger::Debug(LogType::Check, "Main Init Game");
  engine.m_game = std::make_unique<Game>();

  engine.Init();

  while (engine.GetIsRunning()) {
    const float deltaTime = engine.m_time.DeltaTime();
    // const float deltaTime = engine.m_time.DeltaTime();

    // Logger::Debug(LogType::Debug, "Game::Update deltatime: ", deltaTime);

    engine.Events();
    engine.Update(deltaTime);
    engine.Render();
  }

  Logger::Debug(LogType::Check, "Game Exit!");

  /* ##################################################################### */
  /* ##################################################################### */

#ifdef NDEBUG
  Logger::Debug(LogType::Check, "Mode Release!");
#else
  Logger::Debug(LogType::Check, "Mode Debug!");
#endif

  /* ################################################# */

  // Display* d { XOpenDisplay(nullptr) };
  // Screen* s { XDefaultScreenOfDisplay(d) };

  // fmt::print("Size H: {} - W: {}\n", s->height, s->width);

  /* ################################################# */

  return 0;
}

/* NOTE:
 * Solo Clion
Semantic highlightingCopy heading link
Optional semantic highlighting uses different colors for various variables and parameters, making it
easier to recognize and understand your code at a glance.

You can enable it in the settings by going to File | Settings | Editor | Color Scheme | Language
Defaults | Semantic highlighting.

https://devblogs.microsoft.com/cppblog/documentation-for-cpp20-ranges/
 */

// Logger::Debug(LogType::Debug, "Main Init ImGui -- ");
// Logger::Debug(LogType::Debug, "Main Init ImGui -- ");

// IMGUI_CHECKVERSION();
// ImGui::CreateContext();
// ImGui::SetCurrentContext(ImGui::GetCurrentContext());
// ImGuiIO m_io = ImGui::GetIO();
// (void)m_io;
// m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
// m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
// // m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos; // Enable Gamepad Controls
//
// // Setup Dear ImGui style
// ImGui::StyleColorsDark();
// // ImGui::StyleColorsLight();
//
// // Setup Platform/Renderer backends
// ImGui_ImplSDL2_InitForSDLRenderer(
//   engine.GetTextureManager()->GetWindow(), engine.GetTextureManager()->GetRender()
// );
// ImGui_ImplSDLRenderer2_Init(engine.GetTextureManager()->GetRender());
//
// auto* rr = ImGui::GetCurrentContext();
// if (rr) {
//   Logger::Debug(LogType::Debug, "InputSystem::Events --------------- ");
//   Logger::Debug(LogType::Debug, "InputSystem::Events --------------- ");
//   Logger::Debug(LogType::Debug, "InputSystem::Events --------------- ");
//   // ImGui_ImplSDL2_ProcessEvent(&mEvent);
// } else {
//   Logger::Debug(LogType::Error, "InputSystem::Events --------------- ");
//   Logger::Debug(LogType::Error, "InputSystem::Events --------------- ");
//   Logger::Debug(LogType::Error, "InputSystem::Events --------------- ");
// }
//
// Controller::Instance().SetImGuiContext(ImGui::GetCurrentContext());
//
// ImGui_ImplSDL2_InitForOpenGL(
//   engine.GetTextureManager()->GetWindow(), engine.GetCore().GetMainContext()
// );
// ImGui_ImplOpenGL3_Init("#version 330");

// ==========================