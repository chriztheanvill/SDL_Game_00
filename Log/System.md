
> Log::--- Engine ---
> Log::+++ Success all libs!!! +++
> Log::--- Success New Window --- 
> Log::--- Success New Render --- 
> Log::--- Init Game --- 
> Log::InputSystem::Constructor
> Log::Controller::Constructor
Debug::Controller::Detect Controllers detected: 1
Debug::Controller::Detect Controller detected
Debug::Controller::Detect Name: 8BitDo Pro 2
Debug::Controller::Detect Num Axes: 6
Debug::Controller::Detect Num Buttons: 16
> Log::*** *** Node Constructor : 
> Log::TextureManager::Constructor: TextureManager
> Log::--- GameStateManager::Constructor ---

> Log::### State::Constructor :MenuState
> Log::### State::EngineState::Constructor :MenuState
> Log::### MenuState::Constructor : MenuState
Debug::Controller::Detect Controllers detected: 1
Debug::Controller::Detect Controller detected
Debug::Controller::Detect Name: 8BitDo Pro 2
Debug::Controller::Detect Num Axes: 6
Debug::Controller::Detect Num Buttons: 16
> Log::GameStateManager::SetState
Debug::GameStateManager::SetState mCurrent: 0x7ffe3bd8e6f0 - MenuState
Debug::==================MenuState::EnterState==================
> Log::--- Enter to the loop --- 
> Log::DeltaTime: 0.033
Debug::MenuState::Update
Debug::MenuState::Update::Return GameState
> Log::### State::Constructor :GameState
> Log::### State::EngineState::Constructor :GameState
> Log::LevelManager::Constructor. 
Debug::LevelManager::Init 
> Log::*** *** Node Constructor : Level_00
> Log::*** *** Node Constructor : Player
> Log::TransformComponent::Constructor: 
> Log::Character::Constructor: Player
> Log::*** *** Node Constructor : 
> Log::RigidBody::Constructor RigidBody
> Log::TransformComponent::Constructor: 
> Log::Player::Constructor: Player
> Log::--- TextureManager::Load Adding a new texture --- TextureManager::GameState
	name: Vivian
	path: assets/images/Vivian.jpg
> Log::Level::Constructor: Level_00
> Log::Level::Init: Level_00
> Log::*** *** Node Constructor : Level_01
> Log::*** *** Node Constructor : Player
> Log::TransformComponent::Constructor: 
> Log::Character::Constructor: Player
> Log::*** *** Node Constructor : 
> Log::RigidBody::Constructor RigidBody
> Log::TransformComponent::Constructor: 
> Log::Player::Constructor: Player
Debug::--- TextureManager::Load Get a texture ---
name: Vivian
path: assets/images/Vivian.jpg
> Log::Level::Constructor: Level_01
> Log::Level::Init: Level_01

## Warning ----------------------------
LevelManager::Init Choosing level: 0
> Log::### GameState::Constructor :GameState
Debug::GameState::Load
> Log::*** *** Node Constructor : 
> Log::TextureManager::Constructor: TextureManager
> Log::--- TextureManager::Load Adding a new texture --- TextureManager GameState Simple
	name: test
	path: assets/images/bkBlue.png
> Log::~TextureManager::Destructor: TextureManager GameState Simple
> Log::~ NODE Destructor : TextureManager GameState Simple : Address: 0x7ffe3bd8e250
Debug::Controller::Detect Controllers detected: 1
Debug::Controller::Detect Controller detected
Debug::Controller::Detect Name: 8BitDo Pro 2
Debug::Controller::Detect Num Axes: 6
Debug::Controller::Detect Num Buttons: 16
Debug::GameStateManager::Update Updating +++ tmp: 0x7ffe3bd8e478 - GameState
> Log::GameStateManager::SetState
Debug::GameStateManager::SetState mPrev: 0x7ffe3bd8e6f8 - MenuState
Debug::==================MenuState::ExitState==================
Debug::GameStateManager::SetState mCurrent: 0x7ffe3bd8e6f0 - GameState
> Log::==================GameState::EnterState==================
> Log::DeltaTime: 0.14
Debug::Level::Events  Level_00
Debug::Player::Events
Debug::GameState::Update
Debug::Level::Update:: map: Level_00
Debug::Player::Update::mPlayer: x: 0 - y: 0
Debug::Level::Render map: Level_00
Debug::Player::Render
> Log::DeltaTime: 0.033
Debug::Level::Events  Level_00
Debug::Player::Events
Debug::GameState::Update
Debug::Level::Update:: map: Level_00
Debug::Player::Update::mPlayer: x: 0 - y: 0
Debug::Level::Render map: Level_00
Debug::Player::Render
> Log::DeltaTime: 0.033
Debug::Level::Events  Level_00
Debug::Player::Events
Debug::GameState::Update
Debug::Level::Update:: map: Level_00
Debug::Player::Update::mPlayer: x: 0 - y: 0
Debug::Level::Render map: Level_00
Debug::Player::Render
> Log::DeltaTime: 0.033
Debug::Level::Events  Level_00
Debug::Player::Events
Debug::GameState::Update
Debug::Level::Update:: map: Level_00
Debug::Player::Update::mPlayer: x: 0 - y: 0
Debug::Level::Render map: Level_00
Debug::Player::Render
> Log::DeltaTime: 0.033

## Warning ----------------------------
Event, no repeat.

### Error -----------------------------
GameStateManager::Update Quit!!!
> Log::==================GameState::ExitState==================
> Log::### ~GameState::Destructor :GameState
> Log::~LevelManager::Destructor. 
> Log::Level::Destructor: Level_00
> Log::~Player::Destructor: Player
> Log::~TransformComponent::Destructor: 
> Log::~RigidBody::DestructorRigidBody
> Log::~ NODE Destructor : RigidBody : Address: 0x1706b78
> Log::~Character::Destructor: Player
> Log::~TransformComponent::Destructor: 
> Log::~ NODE Destructor : Player : Address: 0x1706ad0
> Log::~ NODE Destructor : Level_00 : Address: 0x1706ab0
> Log::Level::Destructor: Level_01
> Log::~Player::Destructor: Player
> Log::~TransformComponent::Destructor: 
> Log::~RigidBody::DestructorRigidBody
> Log::~ NODE Destructor : RigidBody : Address: 0x170b418
> Log::~Character::Destructor: Player
> Log::~TransformComponent::Destructor: 
> Log::~ NODE Destructor : Player : Address: 0x170b370
> Log::~ NODE Destructor : Level_01 : Address: 0x170b350
> Log::### ~State::EngineState::Destructor :GameState
> Log::### ~State::Destructor :GameState
> Log::### MenuState::Destructor : MenuState
> Log::### ~State::EngineState::Destructor :MenuState
> Log::### ~State::Destructor :MenuState
> Log::--- ~GameStateManager ---
> Log::~TextureManager::Destructor: TextureManager GameState Simple
> Log::~ NODE Destructor : TextureManager GameState Simple : Address: 0x7ffe3bd8e698
> Log::~Controller::Destructor
> Log::~InputSystem::Destructor
Debug::Game Exit!
Debug::Mode Debug!
> Log::--- ~Engine ---