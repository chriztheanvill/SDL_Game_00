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

    // animation.currentTime += deltaTime;
    animation.currentTime += (deltaTime * 1000);

    // Hay que resetar la variable, por que es muy queña
    // if (animation.currentTime == 128) // para float
    if (animation.currentTime < 0) animation.currentTime = animation.lastFrameTime = 0;

    // Logger::Debug(LogType::Check, "AnimationSystem::Update Time: ", animation.currentTime);

    if (animation.currentTime - animation.lastFrameTime
        // >= animation.frames.at(animation.currentFrame).duration / 1000.0f)
        >= animation.frames.at(animation.currentFrame).duration) //
    {
      animation.lastFrameTime = animation.currentTime;
      animation.currentFrame = (animation.currentFrame + 1) % animation.frames.size();
    }

    // if (SDL_GetTicks64() - animation.lastFrameTime
    //     >= animation.frames.at(animation.currentFrame).duration) {
    //   animation.lastFrameTime = SDL_GetTicks64();
    //   animation.currentFrame = (animation.currentFrame + 1) % animation.frames.size();
    // };

    // if (animation.currentTime == 0) {
    //   Logger::Debug(LogType::Log, "AnimationSystem::Update : ", animation.currentTime);
    //   Logger::Debug(LogType::Log, "AnimationSystem::Update : ", animation.lastFrameTime);
    // }
    //
    // Logger::Debug(
    //   LogType::Debug,
    //   "AnimationSystem::Update Time: ",
    //   animation.frames.at(animation.currentFrame).duration / 1000.0f
    // );

    // Logger::Debug(LogType::Log, "AnimationSystem::Update Time: ", animation.currentTime);
    // Logger::Debug(LogType::Debug, "AnimationSystem::Update Time: ", animation.lastFrameTime);
    // Logger::Debug(LogType::Debug, "AnimationSystem::Update Frame: ", animation.currentFrame);

    graphic.src.x = animation.frames.at(animation.currentFrame).src.x;
    graphic.src.y = animation.frames.at(animation.currentFrame).src.y;
  }
}

/*
// Sola una animación
    // animation.currentFrame = (int)((SDL_GetTicks64() - animation.lastFrameTime)
    //                                * animation.frames.at(animation.currentFrame).duration /
    //                                1000.0f)
    //                          % animation.frames.size();


// animation.currentTime += deltaTime;
    // animation.currentFrame
    //   = static_cast<int>(
    //       animation.currentTime * (animation.frames.at(animation.currentFrame).duration / 1000)
    //     )
    //     % animation.frames.size();
 */