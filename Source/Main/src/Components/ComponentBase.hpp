#ifndef COMPONENTBASE_HPP
#define COMPONENTBASE_HPP

#include <cstdint>
#include <string>

enum class ComponentIndex
{
	Transform,
	RigidBody,
	Sprite,
	Tile,
};

struct ComponentBase
{
	uint16_t entityID { };
	std::string componentIndex { };
};

#endif	 // COMPONENTBASE_HPP
