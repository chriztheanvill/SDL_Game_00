#include "State.h"
#include "./GameStateManager.h"

State::State(GameStateManager& gsm)
	: mGameStateManager(gsm)
{
}
State::~State( ) {}

// State* State::Update(const float& deltaTime) { return nullptr; }
std::unique_ptr<State> State::Update(const float& deltaTime) { return nullptr; }
// std::shared_ptr<State> State::Update(const float& deltaTime) { return
// nullptr; }

void State::Render( ) {}
void State::Load( ) {}
void State::Events(SDL_Event& event) {}

void State::EnterState( ) {}
void State::ExitState( ) {}