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

	bool WasJoyButtonPressed(uint8_t button);
	bool WasJoyButtonReleased(uint8_t button);
	bool IsJoyButtonHeld(uint8_t button);

	bool GetIsRunning( ) const { return mIsRunning; }

  protected:
	InputDevice mInputDevice { };
	void SetJoystick(SDL_Joystick* joy) { mJoystick = joy; }
	SDL_Joystick* GetJoystick( ) { return mJoystick; }

  private:
	bool mIsRunning { true };
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

	std::map<uint8_t, bool> mHeldJoyButton;
	std::map<uint8_t, bool> mPressedJoyButton;
	std::map<uint8_t, bool> mReleasedJoyButton;
};

#endif	 // INPUTSYSTEM_H
