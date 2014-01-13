#include "EventArgs.h"

EntityEventArgs::EntityEventArgs(GameEntityInterface* entity)
{
	m_EntityId = entity->id();
}

GameEntityInterface* EntityEventArgs::getEntity() const
{
	return GameEntityInterface::GetAliveById(m_EntityId);
}

int EntityEventArgs::getEntityId() const
{
	return m_EntityId;
}

EntityPositionEventArgs::EntityPositionEventArgs(GameEntityInterface* entity, const Vector2D& pos)
	: EntityEventArgs(entity)
{
	m_Position = pos;
}

Vector2D EntityPositionEventArgs::getPosition() const
{
	return m_Position;
}
