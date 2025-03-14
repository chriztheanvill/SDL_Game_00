#include "Controller.h"

// https://wiki.libsdl.org/SDL2/SDL_GameControllerButton

// std::unique_ptr<Controller> Controller::instance = nullptr; // Old

Controller::Controller() {
  Logger::Debug(LogType::Log, "Controller::Constructor");
  Detect();
}

Controller::~Controller() { Logger::Debug(LogType::Log, "~Controller::Destructor"); }

void Controller::Detect() {
  // Usar un for, para detectar los demas controles
  // Logger::Debug(LogType::Debug, "Controller::Detect Controllers detected: ", SDL_NumJoysticks());
  // Logger::Debug(LogType::Debug, "Controller::Detect Name: ", GetJoystick());

  if (SDL_NumJoysticks() >= 1) {
    if (SDL_IsGameController(0)) { m_controller = SDL_GameControllerOpen(0); }
    // Logger::Debug(LogType::Debug, "Controller::Detect Controller detected");
    // Logger::Debug(
    //   LogType::Debug, "Controller::Detect map: ", SDL_GameControllerMapping(m_controller)
    // );
    // Joystick 1
    // mJoystick = SDL_JoystickOpen(0);
    //
    // if (mJoystick == nullptr) {
    //   Logger::Debug(LogType::Error, "Controller::Detect Error Joystick 0");
    // }

    mInputDevice = InputDevice::Controller;

    // Show info
    //
    // Logger::Debug(LogType::Debug, "Controller::Detect Name: ", SDL_JoystickName(mJoystick));
    // Logger::Debug(
    //   LogType::Debug, "Controller::Detect Num Axes: ", SDL_JoystickNumAxes(GetJoystick())
    // );
    // Logger::Debug(
    //   LogType::Debug, "Controller::Detect Num Buttons: ", SDL_JoystickNumButtons(GetJoystick())
    // );
  } else {
    // Logger::Debug(LogType::Warning, "Controller::Detect ---- Using Keyboard !!!!!!");

    mInputDevice = InputDevice::Keyboard;
    // SetJoystick(nullptr);
  }
}

auto Controller::MoveLeft() -> int {
  // return (
  //   static_cast<int>(KeyHeld(SDL_SCANCODE_LEFT) || KeyHeld(SDL_SCANCODE_A))
  //   || static_cast<int>(ButtonHeld(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
  // );
  return KeyHeld(SDL_SCANCODE_LEFT) || KeyHeld(SDL_SCANCODE_A)
         || ButtonHeld(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
}

auto Controller::MoveRight() -> int {
  return KeyHeld(SDL_SCANCODE_RIGHT) || KeyHeld(SDL_SCANCODE_D)
         || ButtonHeld(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
}

auto Controller::MoveUp() -> int {
  return KeyHeld(SDL_SCANCODE_UP) || KeyHeld(SDL_SCANCODE_W)
         || ButtonHeld(SDL_CONTROLLER_BUTTON_DPAD_UP);
}

auto Controller::MoveDown() -> int {
  return KeyHeld(SDL_SCANCODE_DOWN) || KeyHeld(SDL_SCANCODE_S)
         || ButtonHeld(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
}

auto Controller::ButtonStart() -> bool {
  return KeyHeld(SDL_SCANCODE_RETURN) || ButtonHeld(SDL_CONTROLLER_BUTTON_START);
}
auto Controller::ButtonSelect() -> bool {
  return KeyHeld(SDL_SCANCODE_BACKSLASH) || ButtonHeld(SDL_CONTROLLER_BUTTON_BACK);
}

auto Controller::ButtonA() -> bool {
  return KeyHeld(SDL_SCANCODE_K) || ButtonHeld(SDL_CONTROLLER_BUTTON_A);
}
auto Controller::ButtonB() -> bool {
  return KeyHeld(SDL_SCANCODE_L) || ButtonHeld(SDL_CONTROLLER_BUTTON_B);
}
auto Controller::ButtonX() -> bool {
  return KeyHeld(SDL_SCANCODE_O) || ButtonHeld(SDL_CONTROLLER_BUTTON_X);
}
auto Controller::ButtonY() -> bool {
  return KeyHeld(SDL_SCANCODE_P) || ButtonHeld(SDL_CONTROLLER_BUTTON_Y);
}