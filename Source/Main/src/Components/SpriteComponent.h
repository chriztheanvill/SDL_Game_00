#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "./GraphicComponent.hpp"

struct SpriteComponent : public GraphicComponent {
  SpriteComponent(
	uint16_t entityid = 0,
	std::string name = "Empty",
	SDL_Rect rect = { },
	int16_t zindex = 0,
	SDL_RendererFlip t_flip = SDL_FLIP_NONE
  ) {
	entityID = entityid;
	assetName = name;
	src = rect;
	zIndex = zindex;
	flip = t_flip;
  }

  auto operator==(const SpriteComponent& other) const -> bool { return this == &other; }
  virtual ~SpriteComponent( ) {}
};

#endif	 // SPRITECOMPONENT_HPP
