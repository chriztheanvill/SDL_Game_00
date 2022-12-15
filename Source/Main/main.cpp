/**
 * @file main.cpp
 * @author Cristian Nieto (chriztheanvill@gmail.com)
 * @brief Just a Game
 * @version 0.1
 * @date 2021-02-09
 *
 * @copyright Copyright (c) 2021
 *
 */

// My libs

// System
// #include <iostream>
// #include <memory>
#include <fmt/color.h>

// // For this, in Cmake on Graphics, enable X11
// // #include <X11/Xlib.h>

// #include "./src/Engine.h"
#include "./src/Core/Engine.h"

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

#include <iostream>

class Base
{
  public:
	Base( ) {}
	Base(int age, char* name)
		: mAge(age)
	{
		mName = name;
		// size = sizeof(mName) / sizeof(mName[0]);

		size = strlen(mName);
		std::cout << "\nsize: " << size << "\n";
	}

	Base(const Base& b)
	{
		std::cout << "\nCopy constructor\n";
		mName = b.mName;
		mAge = b.mAge;
		size = b.size;
	}

	Base(Base&& b)
	{
		std::cout << "\nMove constructor\n";
		this->mName = b.mName;
		mAge = b.mAge;
		size = b.size;
		b.mName = nullptr;
		b.mAge = 0;
		b.size = 0;
	}

	void operator=(const Base& b)
	{
		std::cout << "\nCopy\n";
		mName = b.mName;
		mAge = b.mAge;
		size = b.size;
	}

	void operator=(Base&& b)
	{
		std::cout << "\nMove\n";
		this->mName = b.mName;
		mAge = b.mAge;
		size = b.size;
		b.mName = nullptr;
		b.mAge = 0;
		b.size = 0;
	}

	~Base( )
	{
		// delete mName;
		mName = nullptr;
	}

	void Print( )
	{
		if (size == 0) return;
		std::cout << "\n" << mAge << "\n\n";
		for (int i { }; i < size; i++) { std::cout << mName[i] << "\n"; }
	}

  private:
	int mAge;
	char* mName;

	int size { };
};

/* Main */
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	/* ################################################# */

	/* NOTE: Do not use statics
	Engine* e = Engine::GetInstance( );
	e->Init( ); */

	// Delete a smart pointer
	// 	std::unique_ptr<Engine> mEngine { std::make_unique<Engine>( ) };
	// 	mEngine = nullptr;

	// 	// Delete a pointer
	// 	// Engine* mEngine = new Engine( );
	// 	// delete mEngine;
	// 	// mEngine = nullptr;

	// 	/* ################################################# */
	// 	fmt::print("\n\nGame Exit!\n");

	// #ifdef NDEBUG
	// 	fmt::print("\n\n RELEASE!\n");
	// #else
	// 	fmt::print("\n\n Debug!\n");
	// #endif

	/* ################################################# */

	// Display* d { XOpenDisplay(nullptr) };
	// Screen* s { XDefaultScreenOfDisplay(d) };

	// fmt::print("Size H: {} - W: {}\n", s->height, s->width);

	/* ################################################# */

	Base b(99, "123asdAa123----");
	Base c;

	c = (Base &&) b;

	b.Print( );
	c.Print( );
	b.Print( );

	return 0;
}
