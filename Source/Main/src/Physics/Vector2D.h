#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
  public:
	Vector2D( )
		: Vector2D(0, 0)
	{
	}
	Vector2D(const float& x, const float& y)
		: mX(x)
		, mY(y)
	{
	}
	Vector2D(const Vector2D& vec)
		: mX(vec.mX)
		, mY(vec.mY)
	{
	}
	Vector2D(Vector2D&& vec)
	{
		mX = vec.mX;
		mY = vec.mY;

		vec.mX = 0;
		vec.mY = 0;
	}
	// ~Vector2D( );

	static Vector2D Zero( ) { return { }; }
	static Vector2D UP( ) { return { 0, -1 }; }
	static Vector2D DOWN( ) { return { 0, 1 }; }
	static Vector2D LEFT( ) { return { -1, 0 }; }
	static Vector2D RIGHT( ) { return { 1, 0 }; }

	Vector2D& operator=(const Vector2D& vec)
	{
		if (this == &vec) return *this;
		mX = vec.mX;
		mY = vec.mY;
		return *this;
	}

	bool operator==(const Vector2D& vec) const { return this == &vec; }
	bool operator!=(const Vector2D& vec) const { return !(this == &vec); }

	Vector2D operator+(const Vector2D& vec) const
	{
		return { vec.mX + mX, vec.mY + mY };
	}

	Vector2D operator-(const Vector2D& vec) const
	{
		return { vec.mX - mX, vec.mY - mY };
	}

	Vector2D operator*(const Vector2D& vec) const
	{
		return { vec.mX * mX, vec.mY * mY };
	}

	Vector2D operator+(const float& val) const
	{
		return { val + mX, val + mY };
	}

	Vector2D operator-(const float& val) const
	{
		return { val - mX, val - mY };
	}

	Vector2D operator*(const float& val) const
	{
		return { val * mX, val * mY };
	}
	Vector2D operator/(const float& val) const
	{
		if (val <= 0) { return *this; }
		return { val / mX, val / mY };
	}

	friend std::ostream& operator<<(std::ostream& ost, const Vector2D& vec)
	{
		ost << "\nVec X: " << vec.mX << " - mY: " << vec.mY << "\n";
		return ost;
	}

	void Log(const std::string& msg) const
	{
		std::cout << "\n Vector2D -\nmsg: " << msg << " X:" << mX
				  << " - Y: " << mY << "\n";
	}

	void Transform(const Vector2D& vec)
	{
		mX += vec.mX;
		mY += vec.mY;
	}

	void TransformX(const float& x) { mX += x; }
	void TransformY(const float& y) { mY += y; }

	void SetVector(const Vector2D& vec)
	{
		mX = vec.GetX( );
		mY = vec.GetY( );
	}

	Vector2D GetVector( ) const { return { mX, mY }; }

	void SetX(const float& x) { mX = x; }
	void SetY(const float& y) { mY = y; }

	const float& GetX( ) const { return mX; }
	const float& GetY( ) const { return mY; }

  private:
	float mX, mY;
};

#endif	 // VECTOR2D_H
