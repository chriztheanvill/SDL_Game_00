#include "Controller.h"

Controller::Controller(SDL_Event& e)
	: InputSystem(e)
{
	Logger::Debug(LogType::Log, "Controller::Constructor");
	Detect( );
}

Controller::~Controller( )
{
	Logger::Debug(LogType::Log, "~Controller::Destructor");
}

void Controller::Detect( )
{
	// Usar un for, para detectar los demas controles
	Logger::Debug(LogType::Debug,
				  "Controller::Detect Controllers detected: ",
				  SDL_NumJoysticks( ));
	if (SDL_NumJoysticks( ) >= 1)
	{
		Logger::Debug(LogType::Debug, "Controller::Detect Controller detected");
		// Joystick 1
		SetJoystick(SDL_JoystickOpen(0));

		if (GetJoystick( ) == nullptr)
		{
			Logger::Debug(LogType::Error,
						  "Controller::Detect Error Joystick 0");
		}

		mInputDevice = InputDevice::Controller;

		// Show info
		Logger::Debug(LogType::Debug,
					  "Controller::Detect Name: ",
					  SDL_JoystickName(GetJoystick( )));
		Logger::Debug(LogType::Debug,
					  "Controller::Detect Num Axes: ",
					  SDL_JoystickNumAxes(GetJoystick( )));
		Logger::Debug(LogType::Debug,
					  "Controller::Detect Num Buttons: ",
					  SDL_JoystickNumButtons(GetJoystick( )));
	}
	else
	{
		Logger::Debug(LogType::Warning,
					  "Controller::Detect ---- Using Keyboard !!!!!!");

		mInputDevice = InputDevice::Keyboard;
		SetJoystick(nullptr);
	}
}

void Controller::HandleInput( )
{
	if (mInputDevice == InputDevice::Keyboard)
	{
		//
	}
	else   // Controller
	{
		//
	}
}

auto Controller::MoveLeft( ) -> int
{
	return static_cast<int>(
		(IsKeyHeld(SDL_SCANCODE_LEFT) || IsKeyHeld(SDL_SCANCODE_A)));
	// return (IsKeyHeld(SDL_SCANCODE_LEFT) || IsKeyHeld(SDL_SCANCODE_A))	 //
	// 	   || IsJoyButtonHeld(0);
}

auto Controller::MoveRight( ) -> int
{
	return static_cast<int>(IsKeyHeld(SDL_SCANCODE_RIGHT) ||
							IsKeyHeld(SDL_SCANCODE_D));
}

auto Controller::MoveUp( ) -> int
{
	return static_cast<int>(IsKeyHeld(SDL_SCANCODE_UP) ||
							IsKeyHeld(SDL_SCANCODE_W));
}
auto Controller::MoveDown( ) -> int
{
	return static_cast<int>(IsKeyHeld(SDL_SCANCODE_DOWN) ||
							IsKeyHeld(SDL_SCANCODE_S));
}

auto Controller::ButtonStart( ) -> bool
{
	return IsKeyHeld(SDL_SCANCODE_RETURN);
}
auto Controller::ButtonSelect( ) -> bool
{
	return IsKeyHeld(SDL_SCANCODE_BACKSLASH);
}

auto Controller::ButtonA( ) -> bool { return IsKeyHeld(SDL_SCANCODE_K); }
auto Controller::ButtonB( ) -> bool { return IsKeyHeld(SDL_SCANCODE_L); }
auto Controller::ButtonX( ) -> bool { return IsKeyHeld(SDL_SCANCODE_O); }
auto Controller::ButtonY( ) -> bool { return IsKeyHeld(SDL_SCANCODE_P); }
