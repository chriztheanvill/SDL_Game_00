#ifndef RENDERTILEMAPSYSTEM_HPP
#define RENDERTILEMAPSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Graphics/TextureManager.h"
#include "../Components/TransformComponent.hpp"
#include "../Components/TileComponent.hpp"

#include <ranges>
#include <memory>
#include <SDL2/SDL.h>

class RenderTileMapSystem : public System {
  SDL_Renderer* m_render;
  std::unique_ptr<TextureManager>& m_textureManager;

public:
  RenderTileMapSystem(std::unique_ptr<TextureManager>& textureManager)
	: m_textureManager(textureManager) {
	m_render = m_textureManager->GetRender( );
	RequireComponent<TransformComponent>( );
	RequireComponent<TileComponent>( );
  }

  auto Render( ) -> void {
	auto eachEntity = [this](const Entity& entity) -> void {
	  const TransformComponent& transform = entity.GetComponent<TransformComponent>( );
	  const TileComponent& tile = entity.template GetComponent<TileComponent>( );

	  SDL_Rect dst = { //
					   static_cast<int>(transform.position.x * transform.scale.x),
					   static_cast<int>(transform.position.y * transform.scale.y),
					   static_cast<int>(tile.src.w * transform.scale.x),
					   static_cast<int>(tile.src.h * transform.scale.y)
	  };

	  SDL_RenderCopyEx(
		m_render,
		m_textureManager->GetTexture(tile.assetName),
		&tile.src,
		&dst,
		transform.rotation,
		nullptr,
		SDL_FLIP_NONE
	  );

	  // Logger::Debug(
	  //   LogType::Debug,
	  //   "MovementSystem::Update ",
	  //   "X:",
	  //   transform.position.x,
	  //   " - Y: ",
	  //   transform.position.y
	  // );
	};

	std::ranges::for_each(GetEntities( ), eachEntity);
  }
};

#endif	 // RENDERTILEMAPSYSTEM_HPP
