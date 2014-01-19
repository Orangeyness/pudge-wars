#include "pudge-wars/BallEntity.h"

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
	Vector2D diff = hookPosition - m_HookPosition;

	m_Position += diff;

	m_HookPosition = hookPosition;
}

void BallEntity::attachHook(int hookId, const Vector2D& hookPosition)
{
	m_Solid = false;

	m_HookPosition = hookPosition;

	HookableInterface::attachHook(hookId, hookPosition);
}

void BallEntity::dettachHook()
{
	m_Solid = true;

	HookableInterface::dettachHook();
}
