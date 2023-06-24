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

	bool ButtonStart( );
	bool ButtonSelect( );
	// Key A
	bool MoveLeft( );
	// Key D
	bool MoveRight( );
	// Key W
	bool MoveUp( );
	// Key S
	bool MoveDown( );

	// Key K
	bool ButtonA( );
	// Key L
	bool ButtonB( );
	// Key O
	bool ButtonX( );
	// Key P
	bool ButtonY( );

  private:
	InputDevice mInputDevice { };
};

#endif	 // CONTROLLER_H
