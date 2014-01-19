#include "core/events/EventArgs.h"

/*					EntityEventArgs							*/
EntityEventArgs::EntityEventArgs(Entity* entity)
{
	m_EntityId = entity->id();
}

Entity* EntityEventArgs::getEntity() const
{
	return Entity::GetAliveById(m_EntityId);
}

int EntityEventArgs::getEntityId() const
{
	return m_EntityId;
}
/*							--------						*/
/*			DoubleEntityEventArgs : EntityEventArgs			*/

DoubleEntityEventArgs::DoubleEntityEventArgs(
	Entity* entity, 
	Entity* secondEntity)
	: EntityEventArgs(entity)
{
	m_SecondEntityId = secondEntity->id();
}

Entity* DoubleEntityEventArgs::getSecondEntity() const
{
	return Entity::GetAliveById(m_SecondEntityId);
}

int DoubleEntityEventArgs::getSecondEntityId() const
{
	return m_SecondEntityId;
}
/*							--------						*/
/*				PositionEventArgs : EventArgs				*/

PositionEventArgs::PositionEventArgs(const Vector2D& pos)
{
	m_Position = pos;
}

const Vector2D& PositionEventArgs::getPosition() const
{
	return m_Position;
}

/*							--------						*/
/*			EntityPositionEventArgs : EntityEventArgs		*/
EntityPositionEventArgs::EntityPositionEventArgs(
	Entity* entity, 
	const Vector2D& pos)
	: EntityEventArgs(entity), PositionEventArgs(pos)
{ }
/*							--------						*/
/*		DoubleEntityPositionEventArgs : EntityEventArgs		*/

DoubleEntityPositionEventArgs::DoubleEntityPositionEventArgs(
	Entity* entity,
	Entity* secondEntity,
	const Vector2D& pos)
	: 	EntityEventArgs(entity), 
		DoubleEntityEventArgs(entity, secondEntity), 
		PositionEventArgs(pos)
{ }
/*							--------						*/
