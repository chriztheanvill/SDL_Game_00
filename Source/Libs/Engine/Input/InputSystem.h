#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

// #include "../../../Main/src/Game/Game.hpp"

// #include "imgui_impl_sdlrenderer2.h"
#include <SDL2/SDL.h>

#include "../Utils/Logger.h"

#include <map>

enum class InputDevice { Keyboard, Controller };

class InputSystem {
 public:
  InputSystem();
  ~InputSystem();

  void CleanKeyStates();

  auto Events() -> void;

  bool Quit();

  void InputPressed();
  void InputReleased();
  // void InputHolded( );

  auto KeyPressed(SDL_Scancode key) -> bool;
  auto KeyReleased(SDL_Scancode key) -> bool;
  auto KeyHeld(SDL_Scancode key) -> bool;

  auto ButtonPressed(SDL_GameControllerButton button) -> bool;
  auto ButtonReleased(SDL_GameControllerButton button) -> bool;
  auto ButtonHeld(SDL_GameControllerButton button) -> bool;

  auto GetIsRunning() const -> bool { return mIsRunning; }

  auto GetEvents() -> SDL_Event& { return mEvent; }
  // auto SetImGuiContext(ImGuiContext* ctx) -> void {
  //   Logger::Debug(LogType::Log, " ===================InputSystem::SetImGuiContext");
  //   ImGui::SetCurrentContext(ctx);
  //   auto* rr = ImGui::GetCurrentContext();
  // }

 protected:
  InputDevice mInputDevice {};
  void SetJoystick(SDL_Joystick* joy) { mJoystick = joy; }
  auto GetJoystick() -> SDL_Joystick* { return mJoystick; }

  std::map<SDL_Scancode, bool> mHeldKeys;
  std::map<SDL_Scancode, bool> mPressedKeys;
  std::map<SDL_Scancode, bool> mReleasedKeys;

  std::map<SDL_GameControllerButton, bool> mHeldJoyButton;
  std::map<SDL_GameControllerButton, bool> mPressedJoyButton;
  std::map<SDL_GameControllerButton, bool> mReleasedJoyButton;

  SDL_Event mEvent;
  SDL_GameController* m_controller;
  SDL_Joystick* mJoystick;

 private:
  bool mIsRunning { true };

  const Uint8* mKeyState {};
  // Uint8 mKeyStatePressed { };
  // Uint8 mKeyStateReleased { };
  // Uint8 mKeyStateHold { };
  // Uint8 mKeyStatePrev { };
};

#endif // INPUTSYSTEM_H