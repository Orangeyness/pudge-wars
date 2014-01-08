#include "IntroState.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

IntroState::IntroState()
{
	x = 200;
	y = 200;
}

IntroState::~IntroState()
{
}

void IntroState::pause() { }
void IntroState::resume() { }

void IntroState::update(GameEngine* game)
{
	x += 1;
	
	if (x > al_get_bitmap_width(game->screen()))
	{
		x = 0;
	} 
}

void IntroState::draw(GameEngine* game)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));

	al_draw_filled_rectangle(x - 5, y - 5, x + 5, y + 5, al_map_rgb(0, 0, 0));
}

