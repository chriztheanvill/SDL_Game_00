#include "State.h"
#include "../Graphics/TextureManager.h"

// State::State(GameStateManager& gsm, const std::string& name)
State::State(std::string_view name, GameStateManager& gsm, TextureManager& tm)
	: mName(name)
	, mGameStateManager(gsm)
	, mTextureManager(tm)
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

// State* State::Update(const float& deltaTime) { return nullptr; }
std::unique_ptr<State> State::Update(const float& deltaTime) { return nullptr; }
// std::shared_ptr<State> State::Update(const float& deltaTime) { return
// nullptr; }

void State::Render( ) {}
void State::Load( ) { Logger::Debug(LogType::Debug, "### State::Load :"); }
void State::Events(Controller& controller) {}

void State::SetTextureManager(TextureManager& tm, std::string_view name)
{
	mTextureManager = tm;
	mTextureManager.SetName(name);
}

void State::NewTextureManager(TextureManager* tm)
{
	mTextureManager = new TextureManager( );
}

void State::EnterState( ) { Load( ); }
void State::ExitState( ) {}