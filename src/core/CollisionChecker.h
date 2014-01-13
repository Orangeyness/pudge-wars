#ifndef H_COLLISION_CHECKER
#define H_COLLISION_CHECKER

#include "CollidableEntityInterface.h"
#include "RadialEntityInterface.h"
#include "BoundingBoxEntityInterface.h"
#include "GeometryHelper.h"

class CollisionChecker
{
	public:
		static bool isColliding(CollidableEntityInterface* first, CollidableEntityInterface* second);
		static bool isColliding(RadialEntityInterface* first, RadialEntityInterface* second);
		static bool isColliding(BoundingBoxEntityInterface* first, RadialEntityInterface* second);
		static bool isColliding(BoundingBoxEntityInterface* first, BoundingBoxEntityInterface* second);

		static double calculateReflectAngle(CollidableEntityInterface* surface, Vector2D position, double direction);
		static double calculateReflectAngle(RadialEntityInterface* surface, Vector2D position, double direction);
		static double calculateReflectAngle(BoundingBoxEntityInterface* surface, Vector2D position, double direction);

		static double calculateReflectAngle(double surfaceTangent, double direction);
};


#endif
