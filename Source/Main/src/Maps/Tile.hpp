#ifndef TILE_HPP
#define TILE_HPP

struct SDL_Texture;
struct TextureManager;
#include "../Components/GraphicComponent.hpp"
#include "../Utils/Vector2D.h"
#include <utility>
#include <vector>

struct Tile {
  Tile() = default;

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
    std::vector<GraphicComponent::Frame> frames_t
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
      , frames(std::move(frames_t)) { }

  ~Tile() = default;

  Vector2D size;
  Vector2D src;
  Vector2D dst; // Pos
  Vector2D scale;
  std::string name;

  int id {};
  int chunkID {};
  int order {};
  float opacity {};
  float startx {};
  float starty {};
  bool visible {};
  std::vector<GraphicComponent::Frame> frames {};
};

#endif // TILE_HPP
