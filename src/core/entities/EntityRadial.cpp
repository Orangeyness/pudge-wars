#include "core/entities/EntityRadial.h"

#include "core/GameConstants.h"

CollidableType EntityRadial::getType()
{
	return COLLISION_CHECK_RADIAL;
}

double EntityRadial::getRadius()
{
	return m_Radius;
}
