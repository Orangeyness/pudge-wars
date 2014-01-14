#include "CollisionChecker.h"
#include "GameConstants.h"
#include "GameException.h"

bool CollisionChecker::isColliding(
	CollidableEntityInterface* first, CollidableEntityInterface* second)
{
	if (!first->isSolid() || !second->isSolid()) return false;

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


double CollisionChecker::calculateReflectAngle(
	CollidableEntityInterface* surface, Vector2D position, double direction)
{
	RadialEntityInterface* radialEntity = dynamic_cast<RadialEntityInterface*>(surface);
	if (radialEntity != NULL)
	{
		return calculateReflectAngle(radialEntity, position, direction);
	}	

	BoundingBoxEntityInterface* bboxEntity = dynamic_cast<BoundingBoxEntityInterface*>(surface);
	if (bboxEntity != NULL)
	{
		return calculateReflectAngle(bboxEntity, position, direction);
	}	

	THROW_GAME_EXCEPTION(EXCEP_UNEXPECTED_ENTITY_TYPE);
}

double CollisionChecker::calculateReflectAngle(
	RadialEntityInterface* surface, Vector2D position, double direction)
{
	double dir = surface->getPosition().directionToPoint(position);
	double tangent = dir + M_PI / 2;

	return calculateReflectAngle(tangent, direction);
}


double CollisionChecker::calculateReflectAngle(
	BoundingBoxEntityInterface* surface, Vector2D position, double direction)
{
	Rect bBox = surface->getBoundingBox();
	Vector2D moveVector (direction);

	double distBot = std::abs(position.y - bBox.bot());		
	double distTop = std::abs(position.y - bBox.top());		
	double distLeft = std::abs(position.x - bBox.left());
	double distRight = std::abs(position.x - bBox.right());
	double distY = std::min(distBot, distTop);
	double distX = std::min(distLeft, distRight);

	if (moveVector.x != 0 && distX < distY)
	{
		return calculateReflectAngle(Vector2D(0, -1).toDirection(), direction);		
	}
	else
	{
		return calculateReflectAngle(Vector2D(1, 0).toDirection(), direction);		
	}	

	/*
	// Heading left, colliding inside right of box.
	if (moveVector.x < 0 && position.x > bBox.center().x)
	{
		return calculateReflectAngle(Vector2D(0, -1).toDirection(), direction);		
	}
	// Heading right, colliding inside left of box.
	if (moveVector.x > 0 && position.x < bBox.center().x)
	{
		return calculateReflectAngle(Vector2D(0, -1).toDirection(), direction);		
	}
	// Heading up, colliding inside bottom of box.
	if (moveVector.y < 0 && position.y > bBox.center().y)
	{
		return calculateReflectAngle(Vector2D(1, 0).toDirection(), direction);		
	}
	// Heading down, colliding inside top of box.
	if (moveVector.y > 0 && position.y < bBox.center().y)
	{
		return calculateReflectAngle(Vector2D(1, 0).toDirection(), direction);		
	}
	*/

	return direction;
}

double CollisionChecker::calculateReflectAngle(double surfaceTangent, double direction)
{
	double incidenceAngle = 0;
	double diff = direction - surfaceTangent;
	double absDiff = std::abs(diff);
	
	if (absDiff <= M_PI)
	{
		incidenceAngle = (absDiff == M_PI ? absDiff : diff);
	}
	else if (direction > surfaceTangent)
	{
		incidenceAngle = absDiff - 2*M_PI;
	}
	else 
	{
		incidenceAngle = 2*M_PI - absDiff;
	}

	return surfaceTangent - incidenceAngle;
}
