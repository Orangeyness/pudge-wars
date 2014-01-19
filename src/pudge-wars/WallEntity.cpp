#include "pudge-wars/WallEntity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

WallEntity::WallEntity(Vector2D position, double width, double height)
{
	startIgnoringEvents();

	m_Position = position;

	updateBoundingBoxSize(width, height);
}

void WallEntity::draw()
{
	Rect boundingBox = getBoundingBox();

	al_draw_filled_rectangle(boundingBox.left(), boundingBox.top(), 
		boundingBox.right(), boundingBox.bot(), al_map_rgb(200, 0, 0));
}
