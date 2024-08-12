#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "./InputSystem.h"

class Controller : public InputSystem {
public:
  ~Controller( );

  static Controller& Instance( ) {
	static Controller instance { };
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

  void Detect( );

  auto ButtonStart( ) -> bool;
  auto ButtonSelect( ) -> bool;
  // Key A
  auto MoveLeft( ) -> int;
  // Key D
  auto MoveRight( ) -> int;
  // Key W
  auto MoveUp( ) -> int;
  // Key S
  auto MoveDown( ) -> int;

  // Key K
  auto ButtonA( ) -> bool;
  // Key L
  auto ButtonB( ) -> bool;
  // Key O
  auto ButtonX( ) -> bool;
  // Key P
  auto ButtonY( ) -> bool;

private:
  Controller( );
  InputDevice mInputDevice { };

  // static std::unique_ptr<Controller> instance; // Old
};

#endif	 // CONTROLLER_H
