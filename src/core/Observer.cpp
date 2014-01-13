#include "Observer.h"


// Observer

void Observer::startIgnoringEvents()
{
	m_Deaf = true;
}

void Observer::startReceivingEvents()
{	
	m_Deaf = false;
}

bool Observer::isDeaf()
{
	return m_Deaf;
}

void Observer::notify(const Event& event)
{
	if (!isDeaf()) processEvent(event);
}
