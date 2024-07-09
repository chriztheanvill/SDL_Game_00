//
// Created by cris on 11/11/23.
//

#ifndef OBSERVER_H
#define OBSERVER_H

#include "../Utils/Logger.h"
class Subject;

class IObserver
{
  public:
	virtual ~IObserver( ) {}
	virtual auto Update(const std::string& messageFromSubject) -> void = 0;
	virtual auto Remove( ) -> void = 0;
};

class Observer : public IObserver
{
	Subject& mSubject;
	std::string mMessaje;
	int8_t mCurrentObserver { };

  public:
	Observer(Subject& subject);
	virtual ~Observer( );
	auto Update(const std::string& messageFromSubject) -> void override;
	auto Remove( ) -> void override;
};

#endif	 // OBSERVER_H