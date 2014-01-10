#include "EventWithEntity.h"

EventWithEntity::EventWithEntity(EventType type, GameEntityInterface* entity)
	: ObservableEvent(type)
{
	m_EntityId = entity->id();
}

int EventWithEntity::getEntityId()
{
	return m_EntityId;
}
