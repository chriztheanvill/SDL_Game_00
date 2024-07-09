#include "Subject.h"
#include "Observer.h"

Subject::Subject( ) {}
Subject::~Subject( ) { listObservers.clear( ); }

auto Subject::Attach(IObserver* observer) -> void
{
	listObservers.emplace_back(observer);
}

auto Subject::Detach(IObserver* observer) -> void
{
	std::erase(listObservers, observer);
}
auto Subject::Notify( ) -> void
{
	Logger::Debug(LogType::Log,
				  "Subject, Amount of Observers: ",
				  listObservers.size( ));
	for (auto* const tmpList : listObservers) { tmpList->Update(mMessaje); }
}

auto Subject::SetMessage(std::string_view message) -> void
{
	mMessaje = message;
	Notify( );
}