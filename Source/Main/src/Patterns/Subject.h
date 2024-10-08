#ifndef SUBJECT_H
#define SUBJECT_H

#include "../Utils/Logger.h"
#include <vector>

class IObserver;
class Observer;

class ISubject {
public:
  virtual ~ISubject( ) {}
  virtual auto Attach(IObserver* observer) -> void = 0;
  virtual auto Detach(IObserver* observer) -> void = 0;
  virtual auto Notify( ) -> void = 0;
};

class Subject : public ISubject {
  std::vector<IObserver*> m_listObservers;
  std::string m_message;

public:
  Subject( );
  virtual ~Subject( );

  auto Attach(IObserver* observer) -> void override;
  auto Detach(IObserver* observer) -> void override;
  auto Notify( ) -> void override;

  auto SetMessage(std::string_view message) -> void;
};

#endif	 // SUBJECT_H