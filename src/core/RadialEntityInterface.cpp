#include "RadialEntityInterface.h"

#include "GameConstants.h"

CollidableType RadialEntityInterface::getType()
{
	return COLLISION_CHECK_RADIAL;
}

double RadialEntityInterface::getRadius()
{
	return m_Radius;
}
