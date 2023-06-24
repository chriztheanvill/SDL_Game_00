#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

#include <SDL2/SDL.h>

#include "../Core/Node.h"
#include "../Components/Sprite.h"
#include "../Input/Controller.h"

#include "../Components/Transform.hpp"
class Character : public Node
{
  public:
	Character(std::string_view name = "EmptyCharacter")
		: Node(name)
	{
		std::optional<Node> n;

		Logger::Debug(LogType::Log, "Character::Constructor: ", GetName( ));
		mSprite.SetName(name);
	}

	~Character( ) override
	{
		Logger::Debug(LogType::Log, "~Character::Destructor: ", GetName( ));
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

	/* Transform has 3 values:
	Position: Vector2D
	Scale: Vector2D
	Rotacion: doble
	*/
	void SetTransform(const TransformComponent& tc) { mTransform = tc; }
	TransformComponent& GetTransform( ) { return mTransform; }

	void SetPosition(const Vector2D& vec) { mTransform.position = vec; }
	Vector2D& Position( ) { return mTransform.position; }

	void SetScale(const Vector2D& vec) { mTransform.scale = vec; }
	Vector2D& Scale( ) { return mTransform.scale; }

	void SetRotation(const double& rot) { mTransform.rotation = rot; }
	double GetRotation( ) const { return mTransform.rotation; }

	Sprite& GetSprite( ) { return mSprite; }

  private:
	TransformComponent mTransform { };
	SDL_Rect mCollision { };
	SDL_Rect mSrc { };

	// Vector2D mPosition { };
	// Vector2D mSize { };

	Sprite mSprite;
};

#endif	 // CHARACTER_H