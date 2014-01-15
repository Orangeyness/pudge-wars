#include "BallEntity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

BallEntity::BallEntity(Vector2D position, double radius)
{
	startIgnoringEvents();

	m_Position = position;
	m_Radius = radius;
}

void BallEntity::draw()
{
	al_draw_filled_circle(m_Position.x, m_Position.y, m_Radius, al_map_rgb(250, 0, 0));
}

void BallEntity::moveToHook(const Vector2D& hookPosition)
{
	m_Position = hookPosition;
}

void BallEntity::attachHook(int hookId)
{
	m_Solid = false;

	HookableInterface::attachHook(hookId);
}

void BallEntity::dettachHook()
{
	m_Solid = true;

	HookableInterface::dettachHook();
}
