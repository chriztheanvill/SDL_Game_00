/**
 * @file main.cpp
 * @author Cristian Nieto (chriztheanvill@gmail.com)
 * @brief A 2D Game Engine
 * @version 0.1
 * @date 2022-14-12
 *
 * @copyright Copyright (c) 2021
 *
 */

// System

// // For this, in Cmake on Graphics, enable X11
// // #include <X11/Xlib.h>

#include "./src/Core/Engine.h"

// Just for show the icons in VS Code
// NOTE
// DONE
// WARNING
// BUG
// ERROR
// FIXME
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
*/

/* Main */
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	/* ################################################# */

	/* NOTE: Do not use Singleton
		Engine* e = Engine::GetInstance( );
		e->Init( );
	*/

	// Smart pointer
	std::unique_ptr<Engine> mEngine { std::make_unique<Engine>( ) };
	mEngine = nullptr;

	// 	// FIXME (Obsolete)
	// 	// Engine* mEngine = new Engine( );
	// 	// delete mEngine;
	// 	// mEngine = nullptr;

	/* ################################################# */
	fmt::print("\n\nGame Exit!\n");

#ifdef NDEBUG
	fmt::print("\n\n RELEASE!\n");
#else
	fmt::print("\n\n Debug!\n");
#endif

	/* ################################################# */

	// Display* d { XOpenDisplay(nullptr) };
	// Screen* s { XDefaultScreenOfDisplay(d) };

	// fmt::print("Size H: {} - W: {}\n", s->height, s->width);

	/* ################################################# */

	return 0;
}
