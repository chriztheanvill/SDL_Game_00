//
// Created by cris on 11/11/23.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include "../Utils/Logger.h"
class Subject;

class IObserver {
public:
  virtual ~IObserver( ) {}
  virtual auto Update(const std::string& messageFromSubject) -> void = 0;
  virtual auto Remove( ) -> void = 0;
};

class Observer : public IObserver {
  Subject& m_subject;
  std::string m_message;
  int8_t m_currentObserver { };

public:
  Observer(Subject& subject);
  virtual ~Observer( );

  auto Update(const std::string& messageFromSubject) -> void override;
  auto Remove( ) -> void override;
};

#endif	 // OBSERVER_H