#include "Game.hpp"

#include "../ECS/ECS.hpp"
#include "../Utils/Utils.hpp"
#include "../Graphics/TextureManager.h"
#include "../Parsers/MapFileParser.hpp"
//
#include "../Systems/MovementSystem.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/RenderTileMapSystem.hpp"
//
#include "../Components/SpriteComponent.h"
#include "../Input/Controller.h"
// #include "../Game/TileMap.hpp"

// std::vector<std::function<void(std::string)>> Collectable::AUpdate;
// std::function<void( )> Game::dSOme = { };

Game::Game( )
  : m_isrunning(false)
  , m_textureManager(std::make_unique<TextureManager>( ))
  , m_registry(std::make_unique<Registry>( ))
  , m_tileMap(std::make_unique<TileMap>( )) {
  Logger::Debug(LogType::Log, "### Game::Constructor :");

  assert(m_engine.Init( ) || !fprintf(stderr, "Cant load SDL2 framework, INIT \n"));
  assert(
	m_engine.InitGraphics( ) || !fprintf(stderr, "Cant load SDL2 framework, INIT Graphics \n")
  );

  // AUpdate.clear(); // Works
  // Logger::Debug(LogType::Error,"Collectable entered Amount: ", AUpdate.size());
  // for (auto &a : AUpdate) {  a("999");  } // No funciona
  // for (auto a : AUpdate) { (*a)("999"); }
  // dSOme( );

  m_textureManager->SetRender(*m_engine.GetMainRender( ));
  m_time.DeltaTimeStart( );
  m_time.ResetClock( );	  // Borrar
  // Controller::Instance( )->Detect( );
  Controller::Instance( ).Detect( );
}

Game::~Game( ) { Logger::Debug(LogType::Log, "### Game::Destructor :"); }

auto Game::Init( ) -> void {
  /*
   * #####################################
   * ######## Texture Manager ########
   * #####################################
   */
  m_textureManager->AddTexture("Player", "assets/images/bkBlue.png");

  /*
   * #####################################
   * ######## Maps ########
   * #####################################
   */

  MapFileParser m_mapFileParser;
  m_mapFileParser.SetTextureManager(m_textureManager.get( ));
  m_mapFileParser.SetTileMap(m_tileMap);
  const std::expected<bool, std::string>& m_maps = m_mapFileParser.Parse( );
  // if (!m_maps)
  assert(m_maps || !fprintf(stderr, "Cant load TileMap: %s\n", m_maps.error( ).c_str( )));

  m_tileMap->SetRegistry(m_registry);
  LoadLevel(0);

  m_isrunning = true;
}

auto Game::LoadLevel(const uint16_t& level) -> void {
  Logger::Debug(LogType::Check, "Game::LoadLevel00 ", level);

  /*
   * #####################################
   * ######## ECS ########
   * #####################################
   */

  m_registry->AddSystem<MovementSystem>( );
  m_registry->AddSystem<RenderSystem>(m_textureManager);
  m_registry->AddSystem<RenderTileMapSystem>(m_textureManager);

  Entity player = m_registry->NewEntity("Player");

  player.AddComponent<TransformComponent>(Vector2D { 32, 32 }, Vector2D { 1, 1 }, 0.0F);
  player.AddComponent<RigidBodyComponent>(5, GameType::TopDown);
  player.AddComponent<SpriteComponent>("Player", SDL_Rect { 0, 0, 32, 32 }, 1);

  // player.RemoveComponent<SpriteComponent>( );
  // player.DisableComponent<SpriteComponent>( );

  m_tileMap->SelectLevel(level);

  m_registry->Update( );
}

auto Game::Events( ) -> void {
  // OLD
  // Controller::Instance( )->Events( );
  // m_isrunning = Controller::Instance( )->GetIsRunning( );

  Controller::Instance( ).Events( );
  m_isrunning = Controller::Instance( ).GetIsRunning( );
}

auto Game::Update( ) -> void {
  const float deltaTime = m_time.GetDeltaTime( );
  /* ################################################# */
  m_registry->GetSystem<MovementSystem>( )->Update(deltaTime);

  /* ################################################# */
  m_registry->Update( );
}

auto Game::Render( ) -> void {
  // Paint bg color
  SDL_SetRenderDrawColor(m_textureManager->GetRender( ), 60, 60, 60, 255);
  SDL_RenderClear(m_textureManager->GetRender( ));

  /* ################################################# */

  m_registry->GetSystem<RenderTileMapSystem>( )->Render( );
  m_registry->GetSystem<RenderSystem>( )->Render( );

  /* ################################################# */

  // Clean the screen
  SDL_RenderPresent(m_textureManager->GetRender( ));
}

// Logger::Debug(LogType::Log, "Game::Events move left ", Controller::Instance( )->MoveLeft( ));
// Logger::Debug(LogType::Log, "Game::Events m_isrunning ", m_isrunning);

//  while (SDL_PollEvent(&m_event)) {
// switch (m_event.type) {
//   /* ====================== System ====================== */
//   case SDL_QUIT:
// 	Logger::Debug(LogType::Check, "Game::Events, Quitting game by clicking X.");
// 	m_isrunning = false;
//
// 	break;
//   //	//////////////////////////////////////////////////////////////
//   //	//////////////////////////////////////////////////////////////
//
//   /* ====================== Controller ====================== */
//   case SDL_JOYBUTTONDOWN:
//
// 	Logger::Debug(
// 	  LogType::Check,
// 	  "-----------Event Button, Button::",
// 	  static_cast<int>(m_event.jbutton.button)
// 	);
// 	Logger::Debug(LogType::Check, "-----------Event which, Button::", m_event.jbutton.which);
// 	Logger::Debug(
// 	  LogType::Check,
// 	  "-----------Event state, Button::",
// 	  static_cast<int>(m_event.jbutton.state)
// 	);
// 	Logger::Debug(
// 	  LogType::Check,
// 	  "-----------Event type, Button::",
// 	  static_cast<int>(m_event.jbutton.type)
// 	);
// 	if (static_cast<int>(m_event.jbutton.button) == 10)	  // Select
// 	{
// 	  Logger::Debug(LogType::Check, "Event Button, Button::10");
// 	  m_isrunning = false;
// 	}
// 	// if (mEvent.jbutton.button == 0)	  // A
// 	// {
// 	// 	Logger::Debug(LogType::Warning, "Event, Button::A - 0.");
// 	// }
// 	// if (mEvent.jbutton.button == 1)	  // B
// 	// {
// 	// 	Logger::Debug(LogType::Warning, "Event, Button::B - 1.");
// 	// }
// 	// if (mEvent.jbutton.button == 2)	  // X
// 	// {
// 	// 	Logger::Debug(LogType::Warning, "Event, Button::X - 2.");
// 	// }
// 	// if (mEvent.jbutton.button == 3)	  // B
// 	// {
// 	// 	Logger::Debug(LogType::Warning, "Event, Button::Y - 3.");
// 	// }
//
// 	break;
// 	//	//////////////////////////////////////////////////////////////
// 	//	//////////////////////////////////////////////////////////////
//
//   case SDL_JOYBUTTONUP:
// 	Logger::Debug(LogType::Log, "-----------Event which, UP::Button::", m_event.jbutton.which);
// 	Logger::Debug(
// 	  LogType::Log,
// 	  "-----------Event state, UP::Button::",
// 	  static_cast<int>(m_event.jbutton.state)
// 	);
// 	Logger::Debug(
// 	  LogType::Log,
// 	  "-----------Event type, UP::Button::",
// 	  static_cast<int>(m_event.jbutton.type)
// 	);
// 	break;
//
//   /* ====================== Keyboard ====================== */
//   case SDL_KEYDOWN:
// 	// if (m_event.key.repeat == 0) { Logger::Debug(LogType::Note, "Game::Events, no repeat.");
// 	// }
//
// 	if (m_event.key.keysym.sym == SDLK_q || m_event.key.keysym.sym == SDLK_ESCAPE) {
// 	  Logger::Debug(LogType::Check, "Quitting game by Q or Escape.");
// 	  m_isrunning = false;
// 	  // mInputDevice = InputDevice::Keyboard;
// 	  // return false;
// 	}
//
// 	// if (m_event.key.keysym.sym == SDLK_a || m_event.key.keysym.sym == SDLK_LEFT) {
// 	//   m_plPosition.x -= movepl;
// 	//   Logger::Debug(LogType::Check, "Game::Events, move left.", m_plPosition.x);
// 	// } else if (m_event.key.keysym.sym == SDLK_d || m_event.key.keysym.sym == SDLK_RIGHT) {
// 	//   m_plPosition.x += movepl;
// 	//   Logger::Debug(LogType::Check, "Game::Events, move right.", m_plPosition.x);
// 	// }
// 	break;
//
//   //	//////////////////////////////////////////////////////////////
//   //	//////////////////////////////////////////////////////////////
//   //	//////////////////////////////////////////////////////////////
//   //	//////////////////////////////////////////////////////////////
//   case SDL_KEYUP:
// 	// Logger::Debug(LogType::Check, "Game::Events, key up.");
// 	break;
//
//   /* ====================== Mouse ====================== */
//   case SDL_MOUSEMOTION:
// 	// if (m_event.button.x < 200) {
// 	//   Logger::Debug(LogType::Check, "Game::Events, Mouse Pos: ", m_event.button.x);
// 	// }
//
//   default:				break;
// }
// m_registry->GetSystem<MovementSystem>( )->Update(m_time.GetDeltaTime( ));
//  }