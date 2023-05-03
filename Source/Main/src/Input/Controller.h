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

	bool MoveLeft( );
	bool MoveRight( );
	bool MoveUp( );
	bool MoveDown( );

	bool Attack( );
	bool Jump( );
	bool Interact( );

  private:
	InputDevice mInputDevice { };
};

#endif	 // CONTROLLER_H
