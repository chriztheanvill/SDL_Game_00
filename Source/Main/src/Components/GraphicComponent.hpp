#ifndef GRAPHICCOMPONENT_HPP
#define GRAPHICCOMPONENT_HPP

#include <cstdint>
#include <string>
#include <SDL2/SDL.h>

struct GraphicComponent {
	constexpr static const uint16_t SIZE_SMALL = 8;
	constexpr static const uint16_t SIZE_MEDIUM = 16;
	constexpr static const uint16_t SIZE_BIG = 32;
	constexpr static const uint16_t SIZE_LARGE = 64;

	std::string assetName { };
	uint16_t entityID { };
	SDL_Rect src { };
	SDL_RendererFlip flip { };
	int16_t zIndex { };

	// auto operator==(const GraphicComponent& other) const -> bool = default;
	virtual ~GraphicComponent( ) = default;
};

#endif	 // GRAPHICCOMPONENT_HPP
