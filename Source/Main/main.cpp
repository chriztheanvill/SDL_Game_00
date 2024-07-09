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

#include "./src/Game/Game.hpp"

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

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	/* ################################################# */

	/* NOTE: Do not use Singleton
		Engine* e = Engine::GetInstance( );
		e->Init( );
	*/

	Game game;

	game.Init( );

	while (game.IsRunning( ))
	{
		game.Events( );
		game.Update( );
		game.Render( );
	}

	/* ################################################# */
	Logger::Debug(LogType::Debug, "Game Exit!");

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
 * 	GameStateManager::Update
 * 	* Cambiar el estilo de State Machine Finite de apuntadores a usar Enums
 *	* * De la primer manera, se crea el estado, mientras el otro estado esta en
 *uso
 *	* * De la nueva manera, se elimina el estado en uso, y se crea el nuevo
 *

https://devblogs.microsoft.com/cppblog/documentation-for-cpp20-ranges/
 */
