#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

#include <SDL2/SDL.h>

#include "../Core/Node.h"
#include "../Components/Sprite.h"
#include "../Input/Controller.h"

class Character : public Node
{
  public:
	Character(Node* node = nullptr, std::string_view name = "")
		: Node(node, name)
	{
		Logger::Debug(LogType::Log,
					  "--- GameState::Character::Constructor ---");
		mSprite.SetName(name);
	}

	~Character( ) override
	{
		Logger::Debug(LogType::Log, "~GameState::Character::Destructor");
	}

	virtual void Update(const float& deltaTime) = 0;
	virtual void Render( ) = 0;
	virtual void Events(Controller& controller) = 0;

	virtual void SetSprite(SDL_Texture* texture) = 0;
	void SetSpriteRenderer(SDL_Renderer* render)
	{
		mSprite.SetRenderer(render);
	}

  protected:
	SDL_Rect& Collision( ) { return mCollision; }
	SDL_Rect& Src( ) { return mSrc; }

	void SetPosition(const Vector2D& vec) { mPosition = vec; }
	Vector2D& Position( ) { return mPosition; }

	void SetSize(const Vector2D& vec) { mSize = vec; }
	Vector2D& Size( ) { return mSize; }

	Sprite& GetSprite( ) { return mSprite; }

  private:
	SDL_Rect mCollision { };
	SDL_Rect mSrc { };

	Vector2D mPosition { };
	Vector2D mSize { };

	Sprite mSprite;
};

#endif	 // CHARACTER_H