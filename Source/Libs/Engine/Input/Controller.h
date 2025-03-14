#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "./InputSystem.h"

class Controller : public InputSystem {
 public:
  ~Controller();

  static Controller& Instance() {
    static Controller instance {};
    return instance;
  }

  //  OLD
  //  static std::unique_ptr<Controller>& Instance( ) {
  // if (instance == nullptr) {
  //   Logger::Debug(LogType::Debug, "Controller::Instance == nullptr ");
  //   instance.reset(new Controller( ));
  // }
  // return instance;
  //  }

  void Detect();

  auto ButtonStart() -> bool;
  auto ButtonSelect() -> bool;

  auto MoveLeft() -> int;  // Key A
  auto MoveRight() -> int; // Key D
  auto MoveUp() -> int;    // Key W
  auto MoveDown() -> int;  // Key S
  auto ButtonA() -> bool;  // Key K
  auto ButtonB() -> bool;  // Key L
  auto ButtonX() -> bool;  // Key O
  auto ButtonY() -> bool;  // Key P

 private:
  Controller();
  InputDevice mInputDevice {};

  // static std::unique_ptr<Controller> instance; // Old
};

#endif // CONTROLLER_H