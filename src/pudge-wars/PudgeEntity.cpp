#include "PudgeEntity.h"

#include "../core/GeometryHelper.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

PudgeEntity::PudgeEntity(InputProxyInterface* input) 
{
	m_Input = input;	
	m_HookTarget.set(-1, -1);

	x = 200;
	y = 200;
}

entityrtn_t PudgeEntity::update()
{
	if (m_Input->hasMoveDirection())
	{
		Vector2D dir = m_Input->moveDirection();

		x += dir.x;
		y += dir.y;
	}
		
	if (m_Input->hasHookTarget())
	{
		m_HookTarget = m_Input->hookTarget();
	}

	if (x < 0 || y < 0 || x > 400 || y > 400)
	{
		return ENTITY_DELETE;
	}

	return ENTITY_KEEP;
}

void PudgeEntity::draw()
{
	al_draw_filled_rectangle(x - 5, y - 5, x + 5, y + 5, al_map_rgb(0, 0, 0));

	if (m_HookTarget.x > 0 && m_HookTarget.y > 0)
	{
		al_draw_circle(m_HookTarget.x, m_HookTarget.y, 5, al_map_rgb(200, 0, 0), 1);
	}
}

