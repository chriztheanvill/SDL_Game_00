#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "./InputSystem.h"

class Controller : public InputSystem
{
  public:
	Controller(SDL_Event& e);
	~Controller( );

	void Detect( );
	void HandleInput( );

	auto ButtonStart( ) -> bool;
	auto ButtonSelect( ) -> bool;
	// Key A
	auto MoveLeft( ) -> int;
	// Key D
	auto MoveRight( ) -> int;
	// Key W
	auto MoveUp( ) -> int;
	// Key S
	auto MoveDown( ) -> int;

	// Key K
	auto ButtonA( ) -> bool;
	// Key L
	auto ButtonB( ) -> bool;
	// Key O
	auto ButtonX( ) -> bool;
	// Key P
	auto ButtonY( ) -> bool;

  private:
	InputDevice mInputDevice { };
};

#endif	 // CONTROLLER_H
