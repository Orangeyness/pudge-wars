#ifndef H_WALL_ENTITY_
#define H_WALL_ENTITY_

#include "core/entities/EntityBoundingBox.h"
#include "core/helpers/GeometryHelper.h"

class WallEntity : public EntityBoundingBox
{
	public:
		WallEntity(Vector2D position, double width, double height);
		
		virtual void draw();

};

#endif
