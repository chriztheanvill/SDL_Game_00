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

#include "./src/SystemInit.hpp"

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

	fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
			   "--- Start!!! --- ");

	SystemInit sis;
	sis.SetTexture("Level_00", "assets/tilemaps/CaveStory/PrtCave.png");
	sis.SaveTexture("/image.png");

	/* ################################################# */
	fmt::print(fmt::emphasis::bold | fg(fmt::color::alice_blue),
			   "\n\nGame Exit!!! +++\n");

#ifdef NDEBUG
	fmt::print(fmt::emphasis::bold | fg(fmt::color::azure),
			   "\n\nMode Release!\n");
#else
	fmt::print(fmt::emphasis::bold | fg(fmt::color::aqua), "\n\nMode Debug!\n");
#endif

	/* ################################################# */

	// Display* d { XOpenDisplay(nullptr) };
	// Screen* s { XDefaultScreenOfDisplay(d) };

	// fmt::print("Size H: {} - W: {}\n", s->height, s->width);

	/* ################################################# */

	return 0;
}
