#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "./State.h"

// class TextureManager;

class MenuState : public State
{
  public:
	MenuState(GameStateManager& gsm);
	~MenuState( ) override;

	// State* Update(const float& deltaTime) override;
	std::unique_ptr<State> Update(const float& deltaTime) override;
	// std::shared_ptr<State> Update(const float& deltaTime) override;
	void Render( ) override;
	void Load( ) override;
	void Events(SDL_Event& event) override;

	void EnterState( ) override;
	void ExitState( ) override;

  private:
};

#endif	 // MENUSTATE_H
