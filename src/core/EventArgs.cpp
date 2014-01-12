#include "EventArgs.h"

EntityEventArgs::EntityEventArgs(GameEntityInterface* entity)
{
	m_EntityId = entity->id();
}

GameEntityInterface* EntityEventArgs::getEntity() const
{
	return GameEntityInterface::GetAliveById(m_EntityId);
}
