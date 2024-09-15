//
// Created by cris on 9/15/24.
//

#include "AnimationSystem.hpp"

#include "../Components/AnimationComponent.hpp"
#include "../Components/GraphicComponent.hpp"

AnimationSystem::AnimationSystem() {
  RequireComponent<GraphicComponent>();
  RequireComponent<AnimationComponent>();
}

AnimationSystem::~AnimationSystem() { }

auto AnimationSystem::Update(float deltaTime) -> void {
  for (const auto& eachEntity: GetEntities()) {
    auto& animation = eachEntity.GetComponent<AnimationComponent>();
    auto& graphic = eachEntity.GetComponent<GraphicComponent>();

    // animation.currentFrame = ((SDL_GetTicks64() - animation.lastFrameTime)
    //                           * animation.frames.at(animation.currentFrame).duration)
    //                          % animation.frames.size();

    animation.currentTime += (deltaTime * 1000);

    if (animation.currentTime - animation.lastFrameTime
        >= animation.frames.at(animation.currentFrame).duration) {
      animation.lastFrameTime = animation.currentTime;
      animation.currentFrame = (animation.currentFrame + 1) % animation.frames.size();
    }

    graphic.src.x = animation.frames.at(animation.currentFrame).src.x;
    graphic.src.y = animation.frames.at(animation.currentFrame).src.y;
  }
}
