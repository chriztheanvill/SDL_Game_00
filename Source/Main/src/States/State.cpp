#include "State.h"

// State::State(GameStateManager& gsm, const std::string& name)
State::State(std::string_view name)
	: mName(name)
{
	Logger::Debug(LogType::Log, "### State::Constructor :", mName);
}

State::~State( )
{
	Logger::Debug(LogType::Log, "### ~State::Destructor :", mName);
}

/*
#######################################################################################
#######################################################################################
#######################################################################################
#######################################################################################
*/

// std::unique_ptr<State> State::Update(const float& deltaTime) { return

void State::Render( ) {}
void State::Load( ) { Logger::Debug(LogType::Debug, "### State::Load :"); }
void State::Events(Controller& controller) {}

void State::EnterState( ) {}
void State::ExitState( ) {}