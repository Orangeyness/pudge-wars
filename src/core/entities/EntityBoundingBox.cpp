#include "core/entities/EntityBoundingBox.h"
#include "core/GameConstants.h"

CollidableType EntityBoundingBox::getType()
{
	return COLLISION_CHECK_BBOX;
}

void EntityBoundingBox::updateBoundingBoxOrigin(const Vector2D& origin)
{
	m_BoundingBoxOrigin = origin;
}

void EntityBoundingBox::updateBoundingBoxSize(double width, double height)
{
	m_BoundingBoxWidth = width;
	m_BoundingBoxHeight = height;
}

Rect EntityBoundingBox::getBoundingBox()
{
	Rect bBox;
	bBox.position(getPosition(), m_BoundingBoxOrigin);
	bBox.resize(m_BoundingBoxWidth, m_BoundingBoxHeight);

	return bBox;
}
