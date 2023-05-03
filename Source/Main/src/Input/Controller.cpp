#include "Controller.h"

Controller::Controller(SDL_Event& e)
	: InputSystem(e)
{
	Logger::Debug(LogType::Log, "Controller::Constructor");
	// Detect( );
}

Controller::~Controller( )
{
	Logger::Debug(LogType::Log, "~Controller::Destructor");
}

void Controller::Detect( )
{
	// Usar un for, para detectar los demas controles
	// Logger::Debug(LogType::Debug,
	// 			  "Controller::Detect Controllers detected: ",
	// 			  SDL_NumJoysticks( ));
	// if (SDL_NumJoysticks( ) >= 1)
	// {
	// 	Logger::Debug(LogType::Debug, "Controller::Detect Controller detected");
	// 	// Joystick 1
	// 	mJoystick = SDL_JoystickOpen(0);
	// 	if (mJoystick == nullptr)
	// 	{
	// 		Logger::Debug(LogType::Error,
	// 					  "Controller::Detect Error Joystick 0");
	// 	}

	// 	mInputDevice = InputDevice::Controller;

	// 	// Show info
	// 	Logger::Debug(LogType::Debug,
	// 				  "Controller::Detect Name: ",
	// 				  SDL_JoystickName(mJoystick));
	// 	Logger::Debug(LogType::Debug,
	// 				  "Controller::Detect Num Axes: ",
	// 				  SDL_JoystickNumAxes(mJoystick));
	// 	Logger::Debug(LogType::Debug,
	// 				  "Controller::Detect Num Buttons: ",
	// 				  SDL_JoystickNumButtons(mJoystick));
	// }
	// else
	// {
	// 	Logger::Debug(LogType::Warning,
	// 				  "Controller::Detect ---- Using Keyboard !!!!!!");

	// 	mInputDevice = InputDevice::Keyboard;
	// 	mJoystick = nullptr;
	// }
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
	return IsKeyHeld(SDL_SCANCODE_LEFT) || IsKeyHeld(SDL_SCANCODE_A);
}

bool Controller::MoveRight( )
{
	return IsKeyHeld(SDL_SCANCODE_RIGHT) || IsKeyHeld(SDL_SCANCODE_D);
}

bool Controller::MoveUp( ) { return false; }
bool Controller::MoveDown( ) { return false; }

bool Controller::Attack( ) { return false; }
bool Controller::Jump( ) { return false; }
bool Controller::Interact( ) { return false; }
