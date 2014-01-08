#include "PudgeEntity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

PudgeEntity::PudgeEntity() 
{
	x = 200;
	y = 200;
}

entityrtn_t PudgeEntity::update()
{
	if (x++ > 400) x = 0;
	if (y-- < 0) y = 400;

	return ENTITY_KEEP;
}

void PudgeEntity::draw()
{
	al_draw_filled_rectangle(x - 5, y - 5, x + 5, y + 5, al_map_rgb(0, 0, 0));
}

