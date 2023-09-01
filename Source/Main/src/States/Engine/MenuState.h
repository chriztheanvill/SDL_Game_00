#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "./EngineState.hpp"

// class TextureManager;

class MenuState : public EngineState
{
  public:
	MenuState(GameStateManager& gsm, TextureManager& tm);
	~MenuState( ) override;

	auto Update(const float& deltaTime)
		-> std::unique_ptr<EngineState> override;
	void Render( ) override;
	void Load( ) override;
	void Events(Controller& controller) override;

	void EnterState( ) override;
	void ExitState( ) override;

  private:
};

#endif	 // MENUSTATE_H
