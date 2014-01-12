#ifndef H_EVENT_ARGS_
#define H_EVENT_ARGS_

#include "GameEntityInterface.h"

class EventArgs
{
	public:
		virtual	~EventArgs() { }	
};

class EntityEventArgs : public EventArgs
{
	protected:
		int m_EntityId;

	public:
		EntityEventArgs(GameEntityInterface* entity);
		GameEntityInterface* getEntity() const;
};

#endif
