#ifndef GRAPHIC_COMPONENT_HPP
#define GRAPHIC_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "../Utils/Logger.h"

struct GraphicComponent {
  constexpr static const uint16_t SIZE_SMALL = 8;
  constexpr static const uint16_t SIZE_MEDIUM = 16;
  constexpr static const uint16_t SIZE_BIG = 32;
  constexpr static const uint16_t SIZE_LARGE = 64;

  enum class SortLayer : int16_t {
    Last,
    BGx4 = -4,
    BGx2 = -2,
    BG = 0,
    FG = 1, // Player
    FGx2 = 2,
    FGx4 = 4,
    UI = 100,
  };
  using enum SortLayer;

  struct RenderType {
    virtual ~RenderType() = default;
  };

  struct Sprite : public RenderType {
    ~Sprite() override = default;
  };

  struct Tile : public RenderType {
    uint16_t id = 0;
    uint16_t level = 0;
    Tile(uint16_t id_t, uint16_t level_t)
        : id(id_t)
        , level(level_t) { }
    ~Tile() override = default;
  };

  struct Frame {
    SDL_Rect src {};
    float duration {};

    Frame(const SDL_Rect& src_t = {}, float duration_t = 0.f)
        : src(src_t)
        , duration(duration_t) { }
  };

  struct RenderAnimatedType {
    int currentFrame {};
    float currentTime {};
    float lastFrameTime {};
    bool isFinished {};
    bool isActivated {};
    std::vector<Frame> frames;

    RenderAnimatedType(std::vector<Frame> frames_t)
        : frames(std::move(frames_t)) { }
    ~RenderAnimatedType() = default;
  };

  struct SpriteAnimated
      : public Sprite
      , public RenderAnimatedType {
    SpriteAnimated(uint16_t id_t, uint16_t level_t, std::vector<Frame> frames_t)
        : RenderAnimatedType(std::move(frames_t)) { }
    ~SpriteAnimated() override = default;
  };

  struct TileAnimated final
      : public Tile
      , public RenderAnimatedType {
    TileAnimated(uint16_t id_t, uint16_t level_t, std::vector<Frame> frames_t)
        : Tile(id_t, level_t)
        , RenderAnimatedType(std::move(frames_t)) { }
    ~TileAnimated() override = default;
  };

  uint16_t entityID {};
  std::string assetName {};
  SDL_Rect src {};
  int16_t zIndex {};
  std::variant<Tile, TileAnimated, Sprite, SpriteAnimated> type = Tile(0, 0);
  SDL_RendererFlip flip {};

  GraphicComponent(
    uint16_t entityID = 0,
    std::string assetName = "Empty",
    SDL_Rect src = {},
    int16_t zIndex = {},
    SDL_RendererFlip flip = SDL_FLIP_NONE,
    std::variant<Tile, TileAnimated, Sprite, SpriteAnimated> type = Tile(0, 0)
  ) {
    this->entityID = entityID;
    this->assetName = assetName;
    this->src = src;
    this->zIndex = zIndex;
    this->flip = flip;
    this->type = std::move(type);

    // if (dynamic_cast<GraphicComponent::Sprite*>(type.get()) != nullptr) {
    //   Logger::Debug(LogType::Log, "+++ GraphicComponent::GraphicComponent sprite ");
    // }
  }

  ~GraphicComponent() { }

  auto operator==(const GraphicComponent& other) const -> bool { return this == &other; }
  // ~GraphicComponent() = default;
};

#endif // GRAPHIC_COMPONENT_HPP
