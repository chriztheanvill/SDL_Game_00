#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

#include <SDL2/SDL.h>

#include "../Core/Node.h"
#include "../Graphics/Sprite.h"

class Character : public Node
{
  public:
	Character(Node* node = nullptr, std::string_view name = "")
		: Node(node, name)
	{
		Logger::Debug(LogType::Log,
					  "--- GameState::Character::Constructor ---");
	}

	~Character( ) override
	{
		Logger::Debug(LogType::Log, "~GameState::Character::Destructor");
	}

	virtual void Update(const float& deltaTime) = 0;
	virtual void Render( ) = 0;
	virtual void Events(SDL_Event& event) = 0;

	virtual void SetSprite(SDL_Texture* texture) = 0;
	void SetSpriteRenderer(SDL_Renderer* render)
	{
		mSprite.SetRenderer(render);
	}

  protected:
	SDL_Rect& Collision( ) { return mCollision; }
	SDL_Rect& Size( ) { return mSize; }
	Vector2D& Position( ) { return mPosition; }
	RigidBody& GetRigidBody( ) { return mRigidBody; }
	Sprite& GetSprite( ) { return mSprite; }

  private:
	SDL_Rect mCollision { };
	SDL_Rect mSize { };

	Vector2D mPosition { };
	RigidBody mRigidBody { this };

	Sprite mSprite;
};

#endif	 // CHARACTER_H