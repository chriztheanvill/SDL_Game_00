#ifndef ENUMCOMPONENTID_HPP
#define ENUMCOMPONENTID_HPP

#include <cstdint>
#include <vector>

// enum class [[bitset]] ComponentID {
enum class ComponentID : uint8_t {
	None = 0,
	Tranform = 1 << 0,
	Point = 1 << 1,
	RigidBody = 1 << 2,
	Sprite = 1 << 3,
	Tile = 1 << 4,
	SpriteAnimated = 1 << 5,
};

using bits = std::vector<ComponentID>;

// Enable bitwise operations
constexpr ComponentID operator|(ComponentID lhs, ComponentID rhs) {
	return static_cast<ComponentID>(
	  static_cast<std::underlying_type_t<ComponentID>>(lhs)
	  | static_cast<std::underlying_type_t<ComponentID>>(rhs)
	);
}

constexpr ComponentID& operator|=(ComponentID& lhs, ComponentID rhs) {
	lhs = lhs | rhs;
	return lhs;
}

constexpr ComponentID operator&(ComponentID lhs, ComponentID rhs) {
	return static_cast<ComponentID>(
	  static_cast<std::underlying_type_t<ComponentID>>(lhs)
	  & static_cast<std::underlying_type_t<ComponentID>>(rhs)
	);
}

constexpr ComponentID& operator&=(ComponentID& lhs, ComponentID rhs) {
	lhs = lhs & rhs;
	return lhs;
}

constexpr ComponentID operator~(ComponentID flag) {
	return static_cast<ComponentID>(~static_cast<std::underlying_type_t<ComponentID>>(flag));
}

#endif	 // ENUMCOMPONENTID_HPP
