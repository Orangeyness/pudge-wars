#ifndef H_EVENT_
#define H_EVENT_

#include "EventArgs.h"
#include "GameException.h"
#include "GameConstants.h"

typedef unsigned int EventType;

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

		template<typename T> 
		T getArgs() const
		{
			T args = dynamic_cast<T>(m_Args);
			if (args == NULL) THROW_GAME_EXCEPTION(EXCEP_EVENT_WRONG_ARGTYPE);

			return args;
		}
};



#endif
