#ifndef TILE_HPP
#define TILE_HPP

struct SDL_Texture;
struct TextureManager;
#include "../Utils/Vector2D.h"
#include <vector>

struct Tile {
	Tile( ) = default;
	Tile(
	  const Vector2D& size,
	  const Vector2D& sourceTile,
	  const Vector2D& destTile,
	  const Vector2D& scale,
	  const std::string& name,
	  int id,
	  int chunkid,
	  int order,
	  float opacity,
	  float startx,
	  float starty,
	  bool visible,
	  std::vector<std::pair<int, int>> anims,
	  std::vector<int> animationsTime
	)
		: size(size)
		, src(sourceTile)
		, dst(destTile)
		, scale(scale)
		, name(name)
		, id(id)
		, chunkID(chunkid)
		, order(order)
		, opacity(opacity)
		, startx(startx)
		, starty(starty)
		, visible(visible)
		, animationsTime(std::move(animationsTime))
		, animations(std::move(anims)) {
		if (!animations.empty( )) animationsAmount = animations.size( );
	}
	~Tile( ) = default;
	// void Update(float deltaTime);
	// void Render(TextureManager& tm) const;

	Vector2D size;
	Vector2D src;
	Vector2D dst;	// Pos
	Vector2D scale;
	std::string name;

	int id { };
	int chunkID { };
	int order { };
	float opacity { };
	float startx { };
	float starty { };
	bool visible { };
	std::vector<int> animationsTime;
	std::vector<std::pair<int, int>> animations;
	int animationsAmount { };
};

#endif	 // TILE_HPP
