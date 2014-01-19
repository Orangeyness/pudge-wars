#include "core/entities/EntityCollidable.h"

EntityCollidable::EntityCollidable()
{
	m_Solid = true;
}

Vector2D EntityCollidable::getPosition()
{
	return m_Position;
}

bool EntityCollidable::isSolid()
{	
	return m_Solid;
}
