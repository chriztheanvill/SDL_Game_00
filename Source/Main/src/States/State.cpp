#include "State.h"

State::State(GameStateManager& gsm)
	: mGSM(gsm)
{
}
State::~State( ) {}

std::shared_ptr<State> State::Update(const float& deltaTime) { return nullptr; }

void State::Render( ) {}

void State::Events(SDL_Event& event) {}

void State::EnterState( ) {}
void State::ExitState( ) {}