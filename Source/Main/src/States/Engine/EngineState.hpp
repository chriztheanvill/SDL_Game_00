#ifndef ENGINESTATE_HPP
#define ENGINESTATE_HPP

#include "../State.h"
#include "../../Graphics/TextureManager.h"

// class TextureManager;
class GameStateManager;

class EngineState : public State
{
  public:
	EngineState(std::string_view name,
				GameStateManager& gsm,
				TextureManager& tm)
		: State(name)
		, mGameStateManager(gsm)
		, mTextureManager(tm)
	{
		Logger::Debug(LogType::Log,
					  "### State::EngineState::Constructor :",
					  GetName( ));
	}
	virtual ~EngineState( )
	{
		Logger::Debug(LogType::Log,
					  "### ~State::EngineState::Destructor :",
					  GetName( ));
	}

	virtual std::unique_ptr<EngineState> Update(const float& deltaTime) = 0;
	virtual void Render( ) = 0;
	virtual void Load( ) = 0;
	virtual void Events(Controller& controller) = 0;

	virtual void EnterState( ) = 0;
	virtual void ExitState( ) = 0;

	void SetTextureManager(TextureManager& tm, std::string_view name = "new")
	{
		mTextureManager = tm;
		mTextureManager.SetName(name);
	}
	// void NewTextureManager(TextureManager* tm)
	// {
	// 	mTextureManager = new TextureManager(Node( ));
	// }

	GameStateManager& GetGameStateManager( ) const { return mGameStateManager; }

  protected:
	TextureManager& GetTextureManager( ) { return mTextureManager; }

  private:
	TextureManager& mTextureManager;
	GameStateManager& mGameStateManager;
};

#endif	 // ENGINESTATE_HPP