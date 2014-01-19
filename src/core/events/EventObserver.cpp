#include "core/events/EventObserver.h"


// EventObserver

void EventObserver::startIgnoringEvents()
{
	m_Deaf = true;
}

void EventObserver::startReceivingEvents()
{	
	m_Deaf = false;
}

bool EventObserver::isDeaf()
{
	return m_Deaf;
}

void EventObserver::notify(const Event& event)
{
	if (!isDeaf()) processEvent(event);
}
