#ifndef H_WALL_ENTITY_
#define H_WALL_ENTITY_

#include "../core/CollidableEntityInterface.h"
#include "../core/GeometryHelper.h"

class WallEntity : public CollidableEntityInterface
{
	public:
		WallEntity(Vector2D position, double radius);
		
		virtual void draw();

};

#endif
