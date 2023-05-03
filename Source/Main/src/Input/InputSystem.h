#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <SDL2/SDL.h>

#include "../Utils/Logger.h"

#include <map>

enum class InputDevice
{
	Keyboard,
	Controller
};

class InputSystem
{
  public:
	InputSystem(SDL_Event& e);
	~InputSystem( );

	void CleanKeyStates( );

	bool Events( );

	bool Quit( );

	void InputPressed( );
	void InputReleased( );
	void InputHolded( );

	bool WasKeyPressed(SDL_Scancode key);
	bool WasKeyReleased(SDL_Scancode key);
	bool IsKeyHeld(SDL_Scancode key);

  protected:
	InputDevice mInputDevice { };

  private:
	SDL_Event& mEvent;
	SDL_Joystick* mJoystick;

	const Uint8* mKeyState { };
	// Uint8 mKeyStatePressed { };
	// Uint8 mKeyStateReleased { };
	// Uint8 mKeyStateHold { };
	// Uint8 mKeyStatePrev { };

	std::map<SDL_Scancode, bool> mHeldKeys;
	std::map<SDL_Scancode, bool> mPressedKeys;
	std::map<SDL_Scancode, bool> mReleasedKeys;
};

#endif	 // INPUTSYSTEM_H
