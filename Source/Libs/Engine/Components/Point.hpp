#ifndef POINT_HPP
#define POINT_HPP

#include "../Utils/Vector2D.h"

class Point
{
	Vector2D vec;

  public:
	Point( )
		: Point(0, 0)
	{
	}

	Point(const float& x, const float& y)
		: vec(x, y)
	{
	}

  private:
};
#endif	 // POINT_HPP
