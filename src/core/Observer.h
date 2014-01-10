#ifndef H_OBSERVER_
#define H_OBSERVER_

#include <forward_list>

typedef int EventType;

class ObservableEvent 
{
	protected:
		EventType m_Type;

	public:
		ObservableEvent(EventType type);
		EventType getType();
		virtual ~ObservableEvent() { }
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
		virtual ~Observer();
		void notify(ObservableEvent* event);
};


#endif
