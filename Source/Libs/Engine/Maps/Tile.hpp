#ifndef TILE_HPP
#define TILE_HPP

struct SDL_Texture;
struct TextureManager;
#include "../Components/AnimationComponent.hpp"
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
    const uint16_t& scale,
    const std::string& name,
    int id,
    int chunkid,
    int order,
    float opacity,
    float startx,
    float starty,
    bool visible,
    std::vector<AnimationComponent::Frame> frames_t
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
  uint16_t scale;
  std::string name;

  int id {};
  int chunkID {};
  int order {};
  float opacity {};
  float startx {};
  float starty {};
  bool visible {};
  std::vector<AnimationComponent::Frame> frames {};
};

#endif // TILE_HPP