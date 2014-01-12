#include "CollidableEntityInterface.h"

CollidableEntityInterface::CollidableEntityInterface()
{
	m_Solid = true;
}

Vector2D CollidableEntityInterface::getPosition()
{
	return m_Position;
}

bool CollidableEntityInterface::isSolid()
{	
	return m_Solid;
}
