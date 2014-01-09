#ifndef _OBSERVER_
#define _OBSERVER_

#include <forward_list>

typedef int EventType;

class ObservableEvent 
{
	protected:
		EventType m_Type;

	public:
		ObservableEvent(EventType type);
		EventType getType();
};

class Observer 
{
	private:
		std::forward_list<ObservableEvent*> m_EventList;
		bool m_Deaf = false;

	protected:
		bool hasEvents();
		ObservableEvent* eventTop();
		void eventPop();
		void ignoreEvents();
		void receiveEvents();

	public:
		void notify(ObservableEvent* event);
};


#endif
