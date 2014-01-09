#include "CollidableEntityInterface.h"

bool CollidableEntityInterface::isCollidingWith(CollidableEntityInterface* other)
{
	double collisionRange = getRadius() + other->getRadius();
	double distanceSqaured = getPosition().sqauredEuclideanDist(other->getPosition());

 	return (distanceSqaured <= (collisionRange * collisionRange));
}

Vector2D CollidableEntityInterface::getPosition()
{
	return m_Position;
}

double CollidableEntityInterface::getRadius()
{
	return m_Radius;
}
