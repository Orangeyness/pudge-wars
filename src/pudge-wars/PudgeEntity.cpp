#include "PudgeEntity.h"
#include "../core/GeometryHelper.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>

PudgeEntity::PudgeEntity(InputProxyInterface* input) 
  : CollidableEntityInterface()
{
	m_Input = input;	
	m_HookTarget.set(-1, -1);
	m_Radius = 8;
	m_Position.set(200, 200);
}

EntityStatus PudgeEntity::update()
{
	EntityStatus rtn = processEvents();

	if (m_Input->hasMoveDirection())
	{
		Vector2D dir = m_Input->moveDirection();

		m_Position.x += dir.x;
		m_Position.y += dir.y;
	}
		
	if (m_Input->hasHookTarget())
	{
		m_HookTarget = m_Input->hookTarget();
	}

	if (m_Position.x < 0 || 
		m_Position.y < 0 || 
		m_Position.x > 400 || 
		m_Position.y > 400)
	{
		return ENTITY_DEAD;
	}

	return rtn && ENTITY_ALIVE;
}

void PudgeEntity::draw()
{
	al_draw_filled_circle(m_Position.x, m_Position.y, m_Radius, al_map_rgb(0, 0, 250));

	if (m_HookTarget.x > 0 && m_HookTarget.y > 0)
	{
		al_draw_circle(m_HookTarget.x, m_HookTarget.y, 5, al_map_rgb(0, 250, 0), 1);
	}
}

EntityStatus PudgeEntity::processEvents()
{	
	while (hasEvents())
	{
		std::cout << eventTop()->getType() << std::endl;
		
		eventPop();
	}

	return ENTITY_ALIVE;
}
