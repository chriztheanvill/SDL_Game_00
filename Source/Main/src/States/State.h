#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>

#include <memory>

#include "../Input/Controller.h"

#include "../Utils/Logger.h"

class State
{
  public:
	State(std::string_view name);
	virtual ~State( );

	// virtual std::unique_ptr<State> Update(const float& deltaTime) = 0;
	virtual void Render( ) = 0;
	virtual void Load( ) = 0;
	virtual void Events(Controller& controller) = 0;

	virtual void EnterState( ) = 0;
	virtual void ExitState( ) = 0;

	void SetName(std::string_view name = "") { mName = name; }
	[[nodiscard]] auto GetName( ) const -> std::string_view { return mName; }

  private:
	std::string_view mName;
};

#endif	 // STATE_H
