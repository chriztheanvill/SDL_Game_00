#include "InputSystem.h"

InputSystem::InputSystem()
    : mJoystick() {
  Logger::Debug(LogType::Log, "InputSystem::Constructor");
}

InputSystem::~InputSystem() {
  Logger::Debug(LogType::Log, "~InputSystem::Destructor");
  SDL_JoystickClose(mJoystick);
}

auto InputSystem::Events() -> void {
  CleanKeyStates();

  while (SDL_PollEvent(&mEvent)) {
    switch (mEvent.type) {
      case SDL_QUIT:
        Logger::Debug(LogType::Error, "Quitting game by clicking X.");
        mIsRunning = false;

        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_JOYBUTTONDOWN:
        mInputDevice = InputDevice::Controller;
        // Logger::Debug(LogType::Debug, "-----------");
        // Logger::Debug(
        //   LogType::Log,
        //   "-----------Event Button Down, Button::",
        //   static_cast<int>(mEvent.jbutton.button)
        // );
        // Logger::Debug(LogType::Log, "-----------Event which, Button::", mEvent.jbutton.which);
        // Logger::Debug(
        //   LogType::Log, "-----------Event state, Button::",
        //   static_cast<int>(mEvent.jbutton.state)
        // );
        // Logger::Debug(
        //   LogType::Log, "-----------Event type, Button::", static_cast<int>(mEvent.jbutton.type)
        // );
        if (static_cast<int>(mEvent.jbutton.button) == 10) // Select
        {
          Logger::Debug(LogType::Log, "Event Button, Button::10");
          mIsRunning = false;
        }
        // if (mEvent.jbutton.button == 0)	  // A
        // {
        // 	Logger::Debug(LogType::Warning, "Event, Button::A - 0.");
        // }
        // if (mEvent.jbutton.button == 1)	  // B
        // {
        // 	Logger::Debug(LogType::Warning, "Event, Button::B - 1.");
        // }
        // if (mEvent.jbutton.button == 2)	  // X
        // {
        // 	Logger::Debug(LogType::Warning, "Event, Button::X - 2.");
        // }
        // if (mEvent.jbutton.button == 3)	  // B
        // {
        // 	Logger::Debug(LogType::Warning, "Event, Button::Y - 3.");
        // }
        InputPressed();
        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_KEYDOWN:
        if (mEvent.key.repeat == 0) {
          // Logger::Debug(LogType::Warning, "InputSystem::Event, no repeat.");
          InputPressed();
        }

        if (mEvent.key.keysym.sym == SDLK_q || mEvent.key.keysym.sym == SDLK_ESCAPE) {
          Logger::Debug(LogType::Check, "Quitting game by Q or Escape.");
          mIsRunning = false;
          // mInputDevice = InputDevice::Keyboard;
        }

        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_JOYBUTTONUP:
        // Logger::Debug(LogType::Debug, "-----------");
        // Logger::Debug(LogType::Log, "-----------Event which, UP::Button::",
        // mEvent.jbutton.which); Logger::Debug(
        //   LogType::Log,
        //   "-----------Event state, UP::Button::",
        //   static_cast<int>(mEvent.jbutton.state)
        // );
        // Logger::Debug(
        //   LogType::Log, "-----------Event type, UP::Button::",
        //   static_cast<int>(mEvent.jbutton.type)
        // );
        InputReleased();
        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_KEYUP: InputReleased(); break;

      default: break;
    }
    /* ======== ~SYSTEM ======== */

    /* ======== Game ======== */
    // Logger::Debug(LogType::Log, "GameStateManager::Events::Game.");
    // mCurrent->Events(mEvent);
    /* ======== ~Game ======== */
  }

  // mKeyState = SDL_GetKeyboardState(NULL);
}

void InputSystem::CleanKeyStates() {
  mPressedKeys.clear();
  mReleasedKeys.clear();
  // ----------------------------------
  mPressedJoyButton.clear();
  mReleasedJoyButton.clear();
}

void InputSystem::InputPressed() {
  mPressedKeys[mEvent.key.keysym.scancode] = true;
  mHeldKeys[mEvent.key.keysym.scancode] = true;

  // ----------------------------------

  mPressedJoyButton[mEvent.jbutton.button] = true;
  mHeldJoyButton[mEvent.jbutton.button] = true;
}

void InputSystem::InputReleased() {
  mReleasedKeys[mEvent.key.keysym.scancode] = true;
  mHeldKeys[mEvent.key.keysym.scancode] = false;

  // ----------------------------------

  mReleasedJoyButton[mEvent.jbutton.button] = true;
  mHeldJoyButton[mEvent.jbutton.button] = false;
}

// ///////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////

bool InputSystem::WasJoyButtonPressed(const uint8_t& button) { return mPressedJoyButton[button]; }

bool InputSystem::WasJoyButtonReleased(const uint8_t& button) { return mReleasedJoyButton[button]; }

bool InputSystem::IsJoyButtonHeld(const uint8_t& button) { return mHeldJoyButton[button]; }

// ///////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////

bool InputSystem::WasKeyPressed(SDL_Scancode key) { return mPressedKeys[key]; }

bool InputSystem::WasKeyReleased(SDL_Scancode key) { return mReleasedKeys[key]; }

bool InputSystem::IsKeyHeld(SDL_Scancode key) { return mHeldKeys[key]; }

// ///////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////

bool InputSystem::Quit() {
  return (WasKeyPressed(SDL_SCANCODE_Q) || WasKeyPressed(SDL_SCANCODE_ESCAPE));
}

/*
* Logger::Debug(
    LogType::Warning,
    "----------------- IsJoyButtonHeld::",
    static_cast<int>(button),
    " --- ",
    mHeldJoyButton[button]
  );
 */