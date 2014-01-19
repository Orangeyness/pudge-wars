#include "core/entities/EntityCollidable.h"

EntityCollidable::EntityCollidable()
{
	m_Solid = true;
	m_CollisionGroup = COLLISION_GROUP_BASIC;
}

Vector2D EntityCollidable::getPosition()
{
	return m_Position;
}

bool EntityCollidable::isSolid()
{	
	return m_Solid;
}

void EntityCollidable::addCollisionGroup(int group)
{
	m_CollisionGroup = m_CollisionGroup | group;
}

void EntityCollidable::removeCollisionGroup(int group)
{
	m_CollisionGroup = m_CollisionGroup & (~group);
}

int EntityCollidable::getCollisionGroup()
{
	return m_CollisionGroup;
}
