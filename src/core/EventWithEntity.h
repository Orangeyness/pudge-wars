#ifndef _EVENT_WITH_ENTITY_
#define _EVENT_WITH_ENTITY_

#include "Observer.h"
#include "GameEntityInterface.h"

class EventWithEntity : public ObservableEvent
{
	protected:
		int m_EntityId;

	public:
		EventWithEntity(EventType type, GameEntityInterface* entity);
		int getEntityId();
};


#endif
