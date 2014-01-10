#include "Observer.h"

// Base Event
ObservableEvent::ObservableEvent(EventType type)
{
	m_Type = type;
}

EventType ObservableEvent::getType()
{
	return m_Type;
}

ObservableEvent* Observer::eventTop()
{
	return m_EventList.front();
}

// Observer

Observer::~Observer()
{
	while (hasEvents())
	{
		eventPop();
	}
}

void Observer::eventPop()
{
	ObservableEvent* top = m_EventList.front();

	delete top;

	m_EventList.pop_front();
}

void Observer::notify(ObservableEvent* event)
{
	if (m_Deaf)
	{
		delete event;
		return;
	}

	m_EventList.push_front(event);
}

bool Observer::hasEvents()
{
	return !m_EventList.empty();
}

void Observer::ignoreEvents()
{
	m_Deaf = true;
}

void Observer::receiveEvents()
{	
	m_Deaf = false;
}
