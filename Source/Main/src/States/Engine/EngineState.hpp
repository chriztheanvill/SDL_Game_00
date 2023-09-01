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

	virtual auto Update(const float& deltaTime)
		-> std::unique_ptr<EngineState> = 0;
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

	[[nodiscard]] auto GetGameStateManager( ) const -> GameStateManager&
	{
		return mGameStateManager;
	}

  protected:
	auto GetTextureManager( ) -> TextureManager& { return mTextureManager; }

  private:
	TextureManager& mTextureManager;
	GameStateManager& mGameStateManager;
};

#endif	 // ENGINESTATE_HPP