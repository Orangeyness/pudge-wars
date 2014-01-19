#include "pudge-wars/BallEntity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

BallEntity::BallEntity(Vector2D position, double radius)
{
	startIgnoringEvents();

	m_Position = position;
	m_Radius = radius;

	addCollisionGroup(COLLISION_GROUP_HOOKABLE);
}

void BallEntity::draw()
{
	al_draw_filled_circle(m_Position.x, m_Position.y, m_Radius, al_map_rgb(250, 0, 0));
}

void BallEntity::moveToHook(const Vector2D& hookPosition)
{
	Vector2D diff = hookPosition - m_HookPosition;

	m_PositionPrevious = m_Position;
	m_Position += diff;

	m_HookPosition = hookPosition;
}

void BallEntity::attachHook(int hookId, const Vector2D& hookPosition)
{
	removeCollisionGroup(COLLISION_GROUP_BASIC);
	addCollisionGroup(COLLISION_GROUP_PUDGES);

	startReceivingEvents();

	m_HookPosition = hookPosition;

	HookableInterface::attachHook(hookId, hookPosition);
}

void BallEntity::dettachHook()
{
	removeCollisionGroup(COLLISION_GROUP_PUDGES);
	addCollisionGroup(COLLISION_GROUP_BASIC);

	startIgnoringEvents();

	HookableInterface::dettachHook();
}

void BallEntity::processEvent(const Event& event)
{
	switch(event.getType())
	{
		case EVENT_TYPE_COLLISION:
				m_Position = m_PositionPrevious;
				dettachHook();
			break;
	}
}
