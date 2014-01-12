#include "CollisionChecker.h"
#include "GameConstants.h"

bool CollisionChecker::isColliding(
	CollidableEntityInterface* first, CollidableEntityInterface* second)
{
	switch(first->getType())
	{
		case COLLISION_CHECK_RADIAL:
		{
			RadialEntityInterface* circleFirst = dynamic_cast<RadialEntityInterface*>(first);

			if (second->getType() == COLLISION_CHECK_RADIAL) 
			{
				RadialEntityInterface* circleSecond = dynamic_cast<RadialEntityInterface*>(second);
			
				return CollisionChecker::isColliding(circleFirst, circleSecond);
			}
			else
			{
				BoundingBoxEntityInterface* rectSecond = dynamic_cast<BoundingBoxEntityInterface*>(second);
				
				return CollisionChecker::isColliding(rectSecond, circleFirst);
			}

			break;
		}
		case COLLISION_CHECK_BBOX:
		{
			BoundingBoxEntityInterface* rectFirst = dynamic_cast<BoundingBoxEntityInterface*>(first);

			if (second->getType() == COLLISION_CHECK_RADIAL) 
			{
				RadialEntityInterface* circleSecond = dynamic_cast<RadialEntityInterface*>(second);
			
				return CollisionChecker::isColliding(rectFirst, circleSecond);
			}
			else
			{
				BoundingBoxEntityInterface* rectSecond = dynamic_cast<BoundingBoxEntityInterface*>(second);
				
				return CollisionChecker::isColliding(rectFirst, rectSecond);
			}

			break;
		}
	}

	//never
	return false;
}

bool CollisionChecker::isColliding(
	RadialEntityInterface* first, RadialEntityInterface* second)
{
	double collisionRange = first->getRadius() + second->getRadius();
	double distanceSqaured = first->getPosition().sqauredEuclideanDist(second->getPosition());

 	return (distanceSqaured <= (collisionRange * collisionRange));
}

bool CollisionChecker::isColliding(
	BoundingBoxEntityInterface* first, RadialEntityInterface* second)
{
	Rect rFirst = first->getBoundingBox();

	return rFirst.intersects(second->getPosition(), second->getRadius());
}

bool CollisionChecker::isColliding(
	BoundingBoxEntityInterface* first, BoundingBoxEntityInterface* second)
{
	Rect rFirst = first->getBoundingBox();
	Rect rSecond = second->getBoundingBox();

	return rFirst.intersects(rSecond);
}
