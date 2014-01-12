#ifndef H_COLLISION_CHECKER
#define H_COLLISION_CHECKER

#include "CollidableEntityInterface.h"
#include "RadialEntityInterface.h"
#include "BoundingBoxEntityInterface.h"

class CollisionChecker
{
	public:
		static bool isColliding(CollidableEntityInterface* first, CollidableEntityInterface* second);
		static bool isColliding(RadialEntityInterface* first, RadialEntityInterface* second);
		static bool isColliding(BoundingBoxEntityInterface* first, RadialEntityInterface* second);
		static bool isColliding(BoundingBoxEntityInterface* first, BoundingBoxEntityInterface* second);
};


#endif
