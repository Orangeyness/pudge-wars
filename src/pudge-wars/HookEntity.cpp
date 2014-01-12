#include "HookEntity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

HookEntity::HookEntity(Vector2D position, double direction, double speed, int life)
{
	startIgnoringEvents();	

	m_Position = position;
	m_Direction = direction;
	m_Speed = speed;
	m_LifeRemaining = life;
}

EntityStatus HookEntity::update()
{
	m_LifeRemaining --;

	m_Position.x -= lengthdir_x(m_Speed, m_Direction);
	m_Position.y -= lengthdir_y(m_Speed, m_Direction);

	if (m_LifeRemaining > 0)
		return ENTITY_ALIVE;

	return ENTITY_DEAD;
}

void HookEntity::draw()
{
	al_draw_filled_circle(m_Position.x, m_Position.y, 5, al_map_rgb(0, 250, 0));
}
