#ifndef H_EVENT_
#define H_EVENT_

#include "EventArgs.h"

typedef int EventType;

class Event 
{
	protected:
		EventType m_Type;
		EventArgs* m_Args;

	public:
		Event(EventType type);
		Event(EventType type, EventArgs* args);
		EventType getType() const;
		EventArgs* getArgs() const;
};



#endif
