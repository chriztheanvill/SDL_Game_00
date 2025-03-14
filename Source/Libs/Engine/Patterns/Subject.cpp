#include "Subject.h"
#include "Observer.h"

Subject::Subject( ) {}

Subject::~Subject( ) { m_listObservers.clear( ); }

auto Subject::Attach(IObserver* observer) -> void { m_listObservers.emplace_back(observer); }

auto Subject::Detach(IObserver* observer) -> void { std::erase(m_listObservers, observer); }

auto Subject::Notify( ) -> void {
  // Logger::Debug(LogType::Log, "Subject, Amount of Observers: ", m_listObservers.size( ));
  for (auto* const observers : m_listObservers) { observers->Update(m_message); }
}

auto Subject::SetMessage(std::string_view message) -> void {
  m_message = message;
  Notify( );
}