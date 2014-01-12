#ifndef H_WALL_ENTITY_
#define H_WALL_ENTITY_

#include "../core/BoundingBoxEntityInterface.h"
#include "../core/GeometryHelper.h"

class WallEntity : public BoundingBoxEntityInterface
{
	public:
		WallEntity(Vector2D position, double width, double height);
		
		virtual void draw();

};

#endif
