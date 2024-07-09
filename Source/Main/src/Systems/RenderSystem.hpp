#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Graphics/TextureManager.h"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

#include <ranges>
#include <memory>
#include <SDL2/SDL.h>

class RenderSystem : public System {
	SDL_Renderer& m_render;
	std::unique_ptr<TextureManager>& m_textureManager;

  public:
	RenderSystem(SDL_Renderer& render, std::unique_ptr<TextureManager>& textureManager)
		: m_render(render)
		, m_textureManager(textureManager) {
		RequireComponent<TransformComponent>( );
		RequireComponent<SpriteComponent>( );

		// Logger::Debug(LogType::Check, "RenderSystem::RenderSystem ", GetSignature( ));
	}

	auto Render( ) -> void {
		auto eachEntity = [this](const Entity& entity) -> void {
			TransformComponent& transform = entity.GetComponent<TransformComponent>( );
			SpriteComponent& sprite = entity.template GetComponent<SpriteComponent>( );

			// SDL_Rect src = { //
			// 				 static_cast<int>(transform.position.x),
			// 				 static_cast<int>(transform.position.y),
			// 				 static_cast<int>(sprite.width * transform.scale.x),
			// 				 static_cast<int>(sprite.height * transform.scale.y)
			// };

			SDL_Rect dst = { //
							 static_cast<int>(transform.position.x * transform.scale.x),
							 static_cast<int>(transform.position.y * transform.scale.y),
							 static_cast<int>(sprite.src.w * transform.scale.x),
							 static_cast<int>(sprite.src.h * transform.scale.y)
			};

			SDL_RenderCopyEx(
			  &m_render,
			  m_textureManager->GetTexture(sprite.assetName),
			  &sprite.src,
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

#endif	 // RENDERSYSTEM_HPP

		 /**
		 * Solo mostrar un cubo
					 // SDL_SetRenderDrawColor(&m_render, 255, 255, 255, 255);
					 // SDL_RenderFillRect(&m_render, &tmp);
		 */