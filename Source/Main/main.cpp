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

#include "./src/Core/Engine.h"
#include "./src/Core/Time.h"
#include "./src/Game/Game.hpp"
#include "./src/Graphics/TextureManager.h"

// #include "./src/Parsers/MapFileParser.hpp"
#include <cassert>
#include <memory>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
  /* NOTE: Do not use Singleton
      Engine* e = Engine::GetInstance( );
      e->Init( );
  */

  Logger::Debug(LogType::Debug, "Main Init engine");

  Cris::Time time;
  Engine engine;
  bool isvsync {};

  time.SetVSync(isvsync);

  assert(engine.Init() || !fprintf(stderr, "Cant load SDL2 framework, INIT \n"));
  assert(
    engine.InitGraphics(isvsync) || !fprintf(stderr, "Cant load SDL2 framework, INIT Graphics \n")
  );

  /* ##################################################################### */
  /* ##################################################################### */

  Logger::Debug(LogType::Debug, "Main init TextureManager");
  std::shared_ptr<TextureManager> textureManager = std::make_shared<TextureManager>();

  textureManager->SetRender(*engine.GetMainRender());

  /* ##################################################################### */
  /* ##################################################################### */

  // Logger::Debug(LogType::Debug, "Main init Parse Maps");

  /* ##################################################################### */
  /* ##################################################################### */

  Logger::Debug(LogType::Debug, "Main Init Game");

  Game game;

  // game.SetVSyncTimer(false);
  game.SetTextureManager(textureManager);
  game.Init();

  while (game.IsRunning()) {
    const float deltaTime = time.DeltaTime();

    // Logger::Debug(LogType::Debug, "Game::Update deltatime: ", deltaTime);
    game.Events();
    game.Update(deltaTime);
    game.Render(deltaTime);
  }

  Logger::Debug(LogType::Warning, "Game Exit!");

  /* ##################################################################### */
  /* ##################################################################### */

#ifdef NDEBUG
  Logger::Debug(LogType::Debug, "Mode Release!");
#else
  Logger::Debug(LogType::Debug, "Mode Debug!");
#endif

  /* ################################################# */

  // Display* d { XOpenDisplay(nullptr) };
  // Screen* s { XDefaultScreenOfDisplay(d) };

  // fmt::print("Size H: {} - W: {}\n", s->height, s->width);

  /* ################################################# */

  return 0;
}

/* TODO
 * Solo Clion
Semantic highlightingCopy heading link
Optional semantic highlighting uses different colors for various variables and parameters, making it
easier to recognize and understand your code at a glance.

You can enable it in the settings by going to File | Settings | Editor | Color Scheme | Language
Defaults | Semantic highlighting.

https://devblogs.microsoft.com/cppblog/documentation-for-cpp20-ranges/
 */
