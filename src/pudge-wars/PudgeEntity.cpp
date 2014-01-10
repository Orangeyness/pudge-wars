#include "PudgeEntity.h"
#include "../core/GeometryHelper.h"
#include "../core/GameConstants.h"
#include "../core/GameException.h"
#include "../core/EventWithEntity.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <algorithm>
#include <iostream>

PudgeEntity::PudgeEntity(InputProxyInterface* input) 
  : CollidableEntityInterface()
{
	m_Input = input;	
	m_HookTarget.set(-1, -1);
	m_Radius = 20;
	m_Position.set(200, 200);

	m_DirectionCurrent = 0;
	m_DirectionTarget = m_DirectionCurrent;
	m_DirectionTurnRate = DEG_TO_RAD(5);
	m_SpeedCurrent = 0;
	m_SpeedMax = 3;
	m_SpeedAcceleration = 0.5;
	m_SpeedDeceleration = 2;

	m_HookActive = false;
	m_HookRecoveryActive = false;
	m_HookRecoveryTime = 40;
	m_HookRecoveryTimeLeft = 0;
}

EntityStatus PudgeEntity::update()
{
	EntityStatus rtn = processEvents();

	// Get new movement input if not throwing a hook.
	if (m_Input->hasMoveDirection() && !m_HookActive && !m_HookRecoveryActive)
	{
		m_DirectionTarget = m_Input->moveDirection();
	
		m_SpeedCurrent = std::min(m_SpeedCurrent + m_SpeedAcceleration, m_SpeedMax);
	}
		else
	{
		m_SpeedCurrent = std::max(m_SpeedCurrent - m_SpeedDeceleration, 0.0);
	}

	// Determine current direction
	double diff = m_DirectionTarget - m_DirectionCurrent;
	double absoluteDiff = std::abs(diff);
	double rotateDir = diff / absoluteDiff;

	if (absoluteDiff >= M_PI) 
	{
		rotateDir =- rotateDir;
	}	

	if (absoluteDiff < m_DirectionTurnRate)
	{
		m_DirectionCurrent = m_DirectionTarget;
	}
	else
	{
		m_DirectionCurrent += rotateDir * m_DirectionTurnRate;

		if (m_DirectionCurrent >= M_PI)
		{
			m_DirectionCurrent -= M_PI * 2;
		}
		else if (m_DirectionCurrent < -M_PI)
		{
			m_DirectionCurrent += M_PI * 2;
		}
	}

	if (m_HookRecoveryTime > 0 && m_HookRecoveryActive)
	{
		m_HookRecoveryTime -= 1;
	}
	else
	{
		m_HookRecoveryActive = false;
	}
	
	if (m_Input->hasHookTarget() && !m_HookRecoveryActive)
	{
		m_HookActive = true;
		m_HookTarget = m_Input->hookTarget();
		m_DirectionTarget = m_Position.directionToPoint(m_HookTarget);
	}

	if (m_HookActive && m_DirectionCurrent == m_DirectionTarget)
	{
		m_HookActive = false;
		m_HookRecoveryTimeLeft = m_HookRecoveryTime;
		m_HookRecoveryActive = true;
	}

	// Update position if moving

	if (m_SpeedCurrent > m_SpeedAcceleration)
	{
		m_Position.x += lengthdir_x(m_SpeedCurrent, m_DirectionCurrent);
		m_Position.y += lengthdir_y(m_SpeedCurrent, m_DirectionCurrent);
	}
		

	return rtn && ENTITY_ALIVE;
}

void PudgeEntity::draw()
{
	al_draw_filled_circle(m_Position.x, m_Position.y, m_Radius, al_map_rgb(0, 0, 250));

	al_draw_line(	m_Position.x, m_Position.y, 
					m_Position.x + lengthdir_x(m_Radius * 1.2, m_DirectionCurrent),
					m_Position.y + lengthdir_y(m_Radius * 1.2, m_DirectionCurrent),
					al_map_rgb(125, 0, 0), 3
				);

	al_draw_line(	m_Position.x, m_Position.y, 
					m_Position.x + lengthdir_x(m_Radius * 1.2, m_DirectionTarget),
					m_Position.y + lengthdir_y(m_Radius * 1.2, m_DirectionTarget),
					al_map_rgb(0, 125, 0), 3
				);

	if (m_HookActive)
	{
		al_draw_circle(m_HookTarget.x, m_HookTarget.y, 5, al_map_rgb(0, 250, 0), 1);
	}
}

EntityStatus PudgeEntity::processEvents()
{	
	while (hasEvents())
	{
		ObservableEvent* event = eventTop();

		switch(event->getType())
		{
			case EVENT_TYPE_COLLISION:
					EventWithEntity* fullEvent = dynamic_cast<EventWithEntity*>(event);
		
					if (!fullEvent) throw GameException(EXCEP_EVENT_WRONG_TYPE);

					GameEntityInterface* entity = GameEntityInterface::GetAliveById(fullEvent->getEntityId());
	
					m_Position.x -= lengthdir_x(m_SpeedCurrent, m_DirectionCurrent);
					m_Position.y -= lengthdir_y(m_SpeedCurrent, m_DirectionCurrent);
			
					m_SpeedCurrent = 0;
				break;
		}
		
		eventPop();
	}

	return ENTITY_ALIVE;
}
