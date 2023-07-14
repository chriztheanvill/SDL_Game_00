#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Physics/Vector2D.h"
#include "../Physics/RigidBody.h"

#include <SDL2/SDL.h>

#include "../Core/Node.h"
#include "../Components/Sprite.h"
#include "../Input/Controller.h"

#include "../Components/Transform.hpp"

struct CharStats
{
	uint16_t HP { 10 };
	uint16_t HPMax { 10 };
	uint16_t MP { 10 };
	uint16_t MPMax { 10 };

	uint16_t Attack { 1 };
	uint16_t Defence { 1 };

	uint8_t Speed { 200 };
	uint8_t Gravity { 250 };
	uint16_t Jump { 350 };
};

class Character : public Node
{
  public:
	Character(std::string_view name = "EmptyCharacter")
		: Node(name)
	{
		// std::optional<Node> n;

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
	auto Collision( ) -> SDL_Rect& { return mCollision; }

	/* Transform has 3 values:
	Position: Vector2D
	Scale: Vector2D
	Rotacion: doble
	*/
	void SetTransform(const TransformComponent& tc) { mTransform = tc; }
	auto GetTransform( ) -> TransformComponent& { return mTransform; }

	void SetPosition(const Vector2D& vec) { mTransform.position = vec; }
	auto Position( ) -> Vector2D& { return mTransform.position; }

	void SetScale(const Vector2D& vec) { mTransform.scale = vec; }
	auto Scale( ) -> Vector2D& { return mTransform.scale; }

	void SetSize(const Vector2D& vec) { mTransform.size = vec; }
	auto Size( ) -> Vector2D& { return mTransform.size; }

	void SetRotation(const double& rot) { mTransform.rotation = rot; }
	[[nodiscard]] auto GetRotation( ) const -> double
	{
		return mTransform.rotation;
	}

	auto GetSprite( ) -> Sprite& { return mSprite; }

  private:
	TransformComponent mTransform { };
	SDL_Rect mCollision { };
	// SDL_Rect mSrc { };

	// Vector2D mPosition { };
	// Vector2D mSize { };

	Sprite mSprite;
};

#endif	 // CHARACTER_H