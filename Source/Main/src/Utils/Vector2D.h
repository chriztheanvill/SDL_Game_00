#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>

struct Vector2D {
  float x, y;

  Vector2D( )
	: Vector2D(0, 0) {}
  Vector2D(const float& x, const float& y)
	: x(x)
	, y(y) {}
  Vector2D(const Vector2D& vec)
	: x(vec.x)
	, y(vec.y) {}
  Vector2D(Vector2D&& vec) {
	x = vec.x;
	y = vec.y;

	vec.x = 0;
	vec.y = 0;
  }
  // ~Vector2D( );

  static auto Zero( ) -> Vector2D { return { }; }
  static auto UP( ) -> Vector2D { return { 0, -1 }; }
  static auto DOWN( ) -> Vector2D { return { 0, 1 }; }
  static auto LEFT( ) -> Vector2D { return { -1, 0 }; }
  static auto RIGHT( ) -> Vector2D { return { 1, 0 }; }

  auto operator=(const Vector2D& vec) -> Vector2D& {
	if (this == &vec) { return *this; }
	x = vec.x;
	y = vec.y;
	return *this;
  }

  auto operator==(const Vector2D& vec) const -> bool { return this == &vec; }
  auto operator!=(const Vector2D& vec) const -> bool { return !(this == &vec); }
  auto operator+(const Vector2D& vec) const -> Vector2D { return { vec.x + x, vec.y + y }; }
  auto operator-(const Vector2D& vec) const -> Vector2D { return { vec.x - x, vec.y - y }; }
  auto operator*(const Vector2D& vec) const -> Vector2D { return { vec.x * x, vec.y * y }; }
  auto operator+(const float& val) const -> Vector2D { return { val + x, val + y }; }
  auto operator-(const float& val) const -> Vector2D { return { val - x, val - y }; }
  auto operator*(const float& val) const -> Vector2D { return { val * x, val * y }; }
  auto operator/(const float& val) const -> Vector2D {
	if (val <= 0) { return *this; }
	return { val / x, val / y };
  }

  friend auto operator<<(std::ostream& ost, const Vector2D& vec) -> std::ostream& {
	ost << "Vec X: " << vec.x << " - y: " << vec.y;
	return ost;
  }

  void Log(const std::string& msg) const {
	std::cout << "\n Vector2D -\nmsg: " << msg << " X:" << x << " - Y: " << y << "\n";
  }

  void Transform(const Vector2D& vec) {
	x += vec.x;
	y += vec.y;
  }

  void TransformX(const float& t_x) { x += t_x; }
  void TransformY(const float& t_y) { y += t_y; }

  void SetVector(const Vector2D& vec) {
	x = vec.x;
	y = vec.y;
  }

  [[nodiscard]] auto GetVector( ) const -> Vector2D { return { x, y }; }
};

#endif	 // VECTOR2D_HPP
