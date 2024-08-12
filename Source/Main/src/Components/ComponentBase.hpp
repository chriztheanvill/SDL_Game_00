#ifndef COMPONENTBASE_HPP
#define COMPONENTBASE_HPP

#include <cstdint>
#include <string>

enum class ComponentIndex {
	Transform,
	RigidBody,
	Sprite,
	Tile,
	Collider,
};

struct ComponentBase {
	uint16_t entityID { };
	ComponentIndex componentIndex { };
};

#endif	 // COMPONENTBASE_HPP
