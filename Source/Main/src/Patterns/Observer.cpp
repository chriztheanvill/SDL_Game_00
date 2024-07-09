#include "Observer.h"
#include "Subject.h"

Observer::Observer(Subject& subject)
	: mSubject(subject)
{
	subject.Attach(this);
	++mCurrentObserver;
}

Observer::~Observer( ) {}
auto Observer::Update(const std::string& messageFromSubject) -> void
{
	mMessaje = messageFromSubject;
	Logger::Debug(LogType::Log,
				  "Observer num: ",
				  mCurrentObserver,
				  "\n message: ",
				  mMessaje);
}
auto Observer::Remove( ) -> void { mSubject.Detach(this); }