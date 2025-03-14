//
// Created by cris on 9/15/24.
//

#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include <SDL2/SDL.h>
#include <cstdint>
#include <stdfloat>
#include <string>
#include <utility>

#include "../Utils/Logger.h"
#include "../Utils/Vector2D.h"

#include "./ComponentBase.hpp"

// struct AnimationComponent : public Component{
struct AnimationComponent : public ComponentBase {
  struct Frame {
    Vector2D src {};
    uint16_t duration {};

    Frame(const Vector2D& src_t = {}, uint16_t duration_t = 0)
        : src(src_t)
        , duration(duration_t) { }
  };

  uint16_t currentFrame {};
  //
  int_least16_t currentTime {};
  int_least16_t lastFrameTime {};

  // int_fast64_t currentTime {};
  // int_fast64_t lastFrameTime {};

  // float currentTime {};
  // float lastFrameTime {};
  // OK
  // std::float16_t currentTime {};
  // std::float16_t lastFrameTime {};

  bool isFinished {};
  bool isActivated {};
  bool isLoop {};
  std::vector<Frame> frames;
  std::string name;

  AnimationComponent(
    uint64_t entityID_t = 0,
    std::string_view name_t = "Empty",
    std::vector<Frame> frames_t = {},
    bool isLoop_t = true
  )
      : ComponentBase(entityID_t, ComponentIndex::Animation)
      , isLoop(isLoop_t)
      , frames(std::move(frames_t))
      , name(name_t) { }

  auto operator==(const AnimationComponent& other) const -> bool { return this == &other; }
};

#endif // ANIMATIONCOMPONENT_HPP

       /*

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
           bool oneShot {};
           std::vector<Frame> frames;

           RenderAnimatedType(std::vector<Frame> frames_t)
               : frames(std::move(frames_t)) { }
           ~RenderAnimatedType() = default;
         };

         struct SpriteAnimated
             : public Sprite
             , public RenderAnimatedType {
           SpriteAnimated(std::vector<Frame> frames_t)
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
        */