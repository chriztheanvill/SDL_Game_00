#ifndef TILECOMPONENT_HPP
#define TILECOMPONENT_HPP

#include "./GraphicComponent.hpp"

#include <iostream>

struct TileComponent : public GraphicComponent {
	uint16_t level { };
	uint16_t tileID { };

	TileComponent(
	  uint16_t entityid = 0,
	  std::string name = "Empty",
	  uint16_t tileid = 0,
	  uint16_t level = 0,
	  SDL_Rect rect = { }
	) {
		entityID = entityid;
		assetName = name;
		tileID = tileid;
		this->level = level;
		src = rect;
	}

	// auto operator==(const TileComponent& other) const -> bool = default;
	auto operator==(const TileComponent& other) const -> bool {
		return this->entityID == other.entityID;
	}
	// auto operator==(const TileComponent& other) const -> bool { return this == &other; }

	virtual ~TileComponent( ) = default;
};

#endif	 // TILECOMPONENT_HPP
