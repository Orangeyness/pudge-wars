#include "Event.h"

Event::Event(EventType type)
{
	m_Type = type;
	m_Args = NULL;
}

Event::Event(EventType type, EventArgs* args)
{
	m_Type = type;
	m_Args = args;
}

EventType Event::getType() const
{
	return m_Type;
}

EventArgs* Event::getArgs() const
{
	return m_Args;
}

