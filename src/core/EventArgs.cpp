#include "EventArgs.h"

/*					EntityEventArgs							*/
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
/*							--------						*/
/*			DoubleEntityEventArgs : EntityEventArgs			*/

DoubleEntityEventArgs::DoubleEntityEventArgs(
	GameEntityInterface* entity, 
	GameEntityInterface* secondEntity)
	: EntityEventArgs(entity)
{
	m_SecondEntityId = secondEntity->id();
}

GameEntityInterface* DoubleEntityEventArgs::getSecondEntity() const
{
	return GameEntityInterface::GetAliveById(m_SecondEntityId);
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
	GameEntityInterface* entity, 
	const Vector2D& pos)
	: EntityEventArgs(entity), PositionEventArgs(pos)
{ }
/*							--------						*/
/*		DoubleEntityPositionEventArgs : EntityEventArgs		*/

DoubleEntityPositionEventArgs::DoubleEntityPositionEventArgs(
	GameEntityInterface* entity,
	GameEntityInterface* secondEntity,
	const Vector2D& pos)
	: 	EntityEventArgs(entity), 
		DoubleEntityEventArgs(entity, secondEntity), 
		PositionEventArgs(pos)
{ }
/*							--------						*/
