#include "InputSystem.h"

InputSystem::InputSystem(SDL_Event& e)
	: mEvent(e)
	, mJoystick( )
	, mKeyState( )
{
	Logger::Debug(LogType::Log, "InputSystem::Constructor");
}

InputSystem::~InputSystem( )
{
	Logger::Debug(LogType::Log, "~InputSystem::Destructor");
}

void InputSystem::CleanKeyStates( )
{
	mPressedKeys.clear( );
	mReleasedKeys.clear( );
}

bool InputSystem::Events( )
{
	CleanKeyStates( );

	while (SDL_PollEvent(&mEvent))
	{
		switch (mEvent.type)
		{
			case SDL_QUIT:
				Logger::Debug(LogType::Error, "Quitting game by clicking X.");
				return false;
				break;
			case SDL_KEYDOWN:
				if (mEvent.key.repeat == 0)
				{
					Logger::Debug(LogType::Warning, "Event, no repeat.");
					InputPressed( );
				}
				// if (mEvent.key.keysym.sym == SDLK_q ||
				// 	mEvent.key.keysym.sym == SDLK_ESCAPE)
				// {
				// 	Logger::Debug(LogType::Error,
				// 				  "Quitting game by Q or Escape.");
				// 	mInputDevice = InputDevice::Keyboard;
				// 	return false;
				// }
				break;
			case SDL_KEYUP: InputReleased( ); break;
			case SDL_JOYBUTTONDOWN:
				if (mEvent.jbutton.which == 0)
				{
					Logger::Debug(LogType::Log, "Quitting game by Select.");
					mInputDevice = InputDevice::Controller;
				}
				return false;
				break;
			default: break;
		}
		/* ======== ~SYSTEM ======== */

		/* ======== Game ======== */
		// Logger::Debug(LogType::Log, "GameStateManager::Events::Game.");
		// mCurrent->Events(mEvent);
		/* ======== ~Game ======== */
	}

	// mKeyState = SDL_GetKeyboardState(NULL);

	return true;
}

void InputSystem::InputPressed( )
{
	// if key pressed, or button
	mPressedKeys[mEvent.key.keysym.scancode] = true;
	mHeldKeys[mEvent.key.keysym.scancode] = true;
}

void InputSystem::InputReleased( )
{
	mReleasedKeys[mEvent.key.keysym.scancode] = true;
	mHeldKeys[mEvent.key.keysym.scancode] = false;
}

bool InputSystem::WasKeyPressed(SDL_Scancode key)
{
	return mPressedKeys[key];
	// return mKeyState[key];
}

bool InputSystem::WasKeyReleased(SDL_Scancode key)
{
	return mReleasedKeys[key];
}

bool InputSystem::IsKeyHeld(SDL_Scancode key) { return mHeldKeys[key]; }

bool InputSystem::Quit( )
{
	return (WasKeyPressed(SDL_SCANCODE_Q) ||
			WasKeyPressed(SDL_SCANCODE_ESCAPE));
}
