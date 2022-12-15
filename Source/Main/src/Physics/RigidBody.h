#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "./Vector2D.h"

namespace
{
	const int16_t UNI_MASS = 1;
	const float GRAVITY = 9.8F;
}	// namespace

class RigidBody
{
  public:
	RigidBody( )
	{
		mMass = UNI_MASS;
		mGravity = GRAVITY;
	}
	// RigidBody(const RigidBody& other); // Copy
	// RigidBody(RigidBody&& other) noexcept; // Move
	// RigidBody& operator=(const RigidBody& other); // Copy Operator
	// RigidBody& operator=(RigidBody&& other) noexcept; // Move Operator
	~RigidBody( ) = default;   // Virtual is Expensive

	void SetMass(const float& m) { mMass = m; }
	void SetGravity(const float& g) { mGravity = g; }

	void ApplyForce(const Vector2D& v) { mForce = v; }
	void ApplyForceX(const float& v) { mForce.SetX(v); }
	void ApplyForceY(const float& v) { mForce.SetY(v); }
	void UnsetForce( ) { mForce = Vector2D::Zero( ); }
	void UnsetForceX( ) { mForce.SetX(0); }
	void UnsetForceY( ) { mForce.SetY(0); }

	void ApplyFriction(const Vector2D& v) { mFriction = v; }
	void UnsetFriction( ) { mFriction = Vector2D::Zero( ); }

	void Update(const float& deltaTime)
	{
		mAcceleration.SetX((mForce.GetX( ) + mFriction.GetX( )) / mMass);
		mAcceleration.SetY(mGravity + mForce.GetY( ) / mMass);
		mVelocity = mAcceleration * deltaTime;
		mPosition = mVelocity * deltaTime;
	}

	const float& GetMass( ) const { return mMass; }
	const Vector2D& GetPos( ) const { return mPosition; }
	const Vector2D& GetVelocity( ) const { return mVelocity; }
	const Vector2D& GetAcceleration( ) const { return mAcceleration; }

  private:
	float mMass;
	float mGravity;

	Vector2D mForce { 0, 0 };
	Vector2D mFriction { 0, 0 };

	Vector2D mPosition { 0, 0 };
	Vector2D mVelocity { 0, 0 };
	Vector2D mAcceleration { 0, 0 };
};

#endif	 // RIGIDBODY_H