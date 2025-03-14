#include "Observer.h"
#include "Subject.h"

Observer::Observer(Subject& subject)
  : m_subject(subject) {
  subject.Attach(this);
  ++m_currentObserver;
}

Observer::~Observer( ) {}

auto Observer::Update(const std::string& messageFromSubject) -> void {
  m_message = messageFromSubject;
  // Logger::Debug(LogType::Log, "Observer num: ", m_currentObserver, "\n message: ", m_message);
}

auto Observer::Remove( ) -> void { m_subject.Detach(this); }