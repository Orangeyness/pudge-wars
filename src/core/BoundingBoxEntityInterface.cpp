#include "BoundingBoxEntityInterface.h"

#include "GameConstants.h"

CollidableType BoundingBoxEntityInterface::getType()
{
	return COLLISION_CHECK_BBOX;
}

void BoundingBoxEntityInterface::updateBoundingBoxOrigin(const Vector2D& origin)
{
	m_BoundingBoxOrigin = origin;
}

void BoundingBoxEntityInterface::updateBoundingBoxSize(double width, double height)
{
	m_BoundingBoxWidth = width;
	m_BoundingBoxHeight = height;
}

Rect BoundingBoxEntityInterface::getBoundingBox()
{
	Rect bBox;
	bBox.position(getPosition(), m_BoundingBoxOrigin);
	bBox.resize(m_BoundingBoxWidth, m_BoundingBoxHeight);

	return bBox;
}
