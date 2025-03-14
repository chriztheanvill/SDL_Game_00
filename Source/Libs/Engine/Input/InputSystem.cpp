#include "InputSystem.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

InputSystem::InputSystem() { Logger::Debug(LogType::Log, "InputSystem::Constructor"); }

InputSystem::~InputSystem() {
  Logger::Debug(LogType::Check_01, "~InputSystem::Destructor");
  // SDL_JoystickClose(mJoystick);
  SDL_GameControllerClose(m_controller);
}

auto InputSystem::Events() -> void {
  CleanKeyStates();

  while (SDL_PollEvent(&mEvent)) {
    // Logger::Debug(LogType::Debug, "InputSystem::Events --------------- ");
    // auto* rr = ImGui::GetCurrentContext();
    // if (rr) {
    //   Logger::Debug(LogType::Debug, "InputSystem::Events --------------- ");
    //   Logger::Debug(LogType::Debug, "InputSystem::Events --------------- ");
    //   Logger::Debug(LogType::Debug, "InputSystem::Events --------------- ");
    //
    // } else {
    //   Logger::Debug(LogType::Error, "InputSystem::Events --------------- ");
    //   Logger::Debug(LogType::Error, "InputSystem::Events --------------- ");
    //   Logger::Debug(LogType::Error, "InputSystem::Events --------------- ");
    // }
    ImGui_ImplSDL2_ProcessEvent(&mEvent);
    switch (mEvent.type) {
      case SDL_QUIT:
        Logger::Debug(LogType::Error, "Quitting game by clicking X.");
        mIsRunning = false;

        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_CONTROLLERBUTTONDOWN:
      case SDL_JOYBUTTONDOWN:
        // mInputDevice = InputDevice::Controller;

        // if (static_cast<int>(mEvent.jbutton.button) == 10) // Select
        // {
        //   Logger::Debug(LogType::Log, "Event Button, Button::10");
        //   mIsRunning = false;
        // }

        // if (static_cast<int>(mEvent.jbutton.button) == 2) // Select
        //   Logger::Debug(LogType::Check, "Event Button, Button::2");
        // if (static_cast<int>(mEvent.jbutton.button) == 1) // Select
        //   Logger::Debug(LogType::Check, "Event Button, Button::1");
        // if (static_cast<int>(mEvent.jbutton.button) == 0) // Select
        //   Logger::Debug(LogType::Check, "Event Button, Button::0");
        //
        // Logger::Debug(
        //   LogType::Check, "Event Button, Button::", static_cast<int>(mEvent.jbutton.button)
        // );

        mInputDevice = InputDevice::Controller;

        InputPressed();
        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_KEYDOWN:

        if (mEvent.key.keysym.sym == SDLK_q || mEvent.key.keysym.sym == SDLK_ESCAPE) {
          Logger::Debug(LogType::Check, "Quitting game by Q or Escape.");
          mIsRunning = false;
        }
        mInputDevice = InputDevice::Keyboard;

        if (mEvent.key.repeat == 0) {
          // Logger::Debug(LogType::Warning, "InputSystem::Event, no repeat.");
          InputPressed();
        }

        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_CONTROLLERBUTTONUP:
      case SDL_JOYBUTTONUP:
        mInputDevice = InputDevice::Controller;
        InputReleased();
        break;
        //	//////////////////////////////////////////////////////////////
        //	//////////////////////////////////////////////////////////////
      case SDL_KEYUP:
        mInputDevice = InputDevice::Keyboard;
        InputReleased();
        break;

      default: break;
    } // Switch
  }
}

void InputSystem::CleanKeyStates() {
  mPressedKeys.clear();
  mReleasedKeys.clear();
  // ----------------------------------
  mPressedJoyButton.clear();
  mReleasedJoyButton.clear();
}

void InputSystem::InputPressed() {
  if (mInputDevice == InputDevice::Keyboard) {
    mPressedKeys[mEvent.key.keysym.scancode] = true;
    mHeldKeys[mEvent.key.keysym.scancode] = true;

  } else {
    SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(mEvent.cbutton.button);

    mPressedJoyButton[button] = true;
    mHeldJoyButton[button] = true;
  }
}

void InputSystem::InputReleased() {
  if (mInputDevice == InputDevice::Keyboard) {
    // Logger::Debug(LogType::Check, "----------------- InputSystem::InputReleased() Keyboard");
    mReleasedKeys[mEvent.key.keysym.scancode] = true;
    mHeldKeys[mEvent.key.keysym.scancode] = false;
  } else {
    // Logger::Debug(LogType::Check, "----------------- InputSystem::InputReleased() Controller");

    SDL_GameControllerButton button = static_cast<SDL_GameControllerButton>(mEvent.cbutton.button);

    mReleasedJoyButton[button] = true;
    mHeldJoyButton[button] = false;
  }
}

// ///////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////

bool InputSystem::ButtonPressed(SDL_GameControllerButton button) {
  return mPressedJoyButton[button];
}

bool InputSystem::ButtonReleased(SDL_GameControllerButton button) {
  return mReleasedJoyButton[button];
}

bool InputSystem::ButtonHeld(SDL_GameControllerButton button) { return mHeldJoyButton[button]; }

// ///////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////

bool InputSystem::KeyPressed(SDL_Scancode key) { return mPressedKeys[key]; }

bool InputSystem::KeyReleased(SDL_Scancode key) { return mReleasedKeys[key]; }

bool InputSystem::KeyHeld(SDL_Scancode key) { return mHeldKeys[key]; }

// ///////////////////////////////////////////////////////////////////
// ///////////////////////////////////////////////////////////////////

bool InputSystem::Quit() { return (KeyPressed(SDL_SCANCODE_Q) || KeyPressed(SDL_SCANCODE_ESCAPE)); }

/*
* Logger::Debug(
    LogType::Warning,
    "----------------- IsJoyButtonHeld::",
    static_cast<int>(button),
    " --- ",
    mHeldJoyButton[button]
  );
 */

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

/* ======== ~SYSTEM ======== */

/* ======== Game ======== */
// Logger::Debug(LogType::Log, "GameStateManager::Events::Game.");
// mCurrent->Events(mEvent);
/* ======== ~Game ======== */

// mKeyState = SDL_GetKeyboardState(NULL);