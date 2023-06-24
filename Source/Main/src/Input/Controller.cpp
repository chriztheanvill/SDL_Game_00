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

bool Controller::MoveLeft( )
{
	return (IsKeyHeld(SDL_SCANCODE_LEFT) || IsKeyHeld(SDL_SCANCODE_A));
	// return (IsKeyHeld(SDL_SCANCODE_LEFT) || IsKeyHeld(SDL_SCANCODE_A))	 //
	// 	   || IsJoyButtonHeld(0);
}

bool Controller::MoveRight( )
{
	return IsKeyHeld(SDL_SCANCODE_RIGHT) || IsKeyHeld(SDL_SCANCODE_D);
}

bool Controller::MoveUp( )
{
	return IsKeyHeld(SDL_SCANCODE_UP) || IsKeyHeld(SDL_SCANCODE_W);
}
bool Controller::MoveDown( )
{
	return IsKeyHeld(SDL_SCANCODE_DOWN) || IsKeyHeld(SDL_SCANCODE_S);
}

bool Controller::ButtonStart( ) { return IsKeyHeld(SDL_SCANCODE_RETURN); }
bool Controller::ButtonSelect( ) { return IsKeyHeld(SDL_SCANCODE_BACKSLASH); }

bool Controller::ButtonA( ) { return IsKeyHeld(SDL_SCANCODE_K); }
bool Controller::ButtonB( ) { return IsKeyHeld(SDL_SCANCODE_L); }
bool Controller::ButtonX( ) { return IsKeyHeld(SDL_SCANCODE_O); }
bool Controller::ButtonY( ) { return IsKeyHeld(SDL_SCANCODE_P); }
