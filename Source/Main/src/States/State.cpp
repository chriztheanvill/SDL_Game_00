#include "State.h"
#include "./GameStateManager.h"

State::State(GameStateManager& gsm, const std::string& name)
	: mGameStateManager(gsm)
	, Node(nullptr, name)
{
	std::cout << "\n\n ### State::Destructor : " << GetName( ) << " : ###";
}
State::~State( )
{
	//
	std::cout << "\n\n ### ~State::Destructor : " << GetName( ) << " : ###";
}

// State* State::Update(const float& deltaTime) { return nullptr; }
std::unique_ptr<State> State::Update(const float& deltaTime) { return nullptr; }
// std::shared_ptr<State> State::Update(const float& deltaTime) { return
// nullptr; }

void State::Render( ) {}
void State::Load( ) {}
void State::Events(SDL_Event& event) {}

void State::EnterState( ) {}
void State::ExitState( ) {}