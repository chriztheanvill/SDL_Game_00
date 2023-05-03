#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "./State.h"

// class TextureManager;

class MenuState : public State
{
  public:
	MenuState(GameStateManager& gsm, TextureManager& tm);
	~MenuState( ) override;

	std::unique_ptr<State> Update(const float& deltaTime) override;
	void Render( ) override;
	void Load( ) override;
	void Events(Controller& controller) override;

	void EnterState( ) override;
	void ExitState( ) override;

  private:
};

#endif	 // MENUSTATE_H
