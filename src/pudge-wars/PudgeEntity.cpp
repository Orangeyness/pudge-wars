#include "pudge-wars/PudgeEntity.h"

#include "core/GameConstants.h"
#include "core/GameException.h"
#include "core/services/ServiceLocator.h"
#include "core/helpers/GeometryHelper.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <algorithm>

PudgeEntity::PudgeEntity(InputProxyInterface* input) 
{
	m_Input = input;	
	m_HookTarget.set(-1, -1);
	m_Radius = 20;
	m_Position.set(200, 200);

	m_DirectionCurrent = 0;
	m_DirectionTarget = m_DirectionCurrent;
	m_DirectionTurnRate = DEG_TO_RAD(20);
	m_SpeedCurrent = 0;
	m_SpeedMax = 4;
	m_SpeedAcceleration = 0.5;
	m_SpeedDeceleration = 2;

	m_HookActive = false;
	m_HookRecoveryActive = false;
	m_HookRecoveryTime = 40;
	m_HookRecoveryTimeLeft = 0;

	addCollisionGroup(COLLISION_GROUP_PUDGES);
}

EntityStatus PudgeEntity::update()
{
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
		m_SpeedCurrent = 0;
	}

	if (m_HookActive && m_DirectionCurrent == m_DirectionTarget)
	{
		ServiceLocator::GetEventService()->broadcast(Event(EVENT_TYPE_SPAWN_HOOK, new EntityEventArgs(this)));

		m_HookActive = false;
		m_HookRecoveryTimeLeft = m_HookRecoveryTime;
		m_HookRecoveryActive = true;
	}

	// Update position if moving

	if (m_SpeedCurrent > 0)
	{
		m_Position.x += lengthdir_x(m_SpeedCurrent, m_DirectionCurrent);
		m_Position.y += lengthdir_y(m_SpeedCurrent, m_DirectionCurrent);

		ServiceLocator::GetEventService()->broadcast(Event(EVENT_TYPE_ENTITY_MOVE, new EntityPositionEventArgs(this, m_Position)));
	}
		
	return ENTITY_ALIVE;
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
}

void PudgeEntity::processEvent(const Event& event)
{	
	switch(event.getType())
	{
		case EVENT_TYPE_COLLISION:
				m_Position.x -= lengthdir_x(m_SpeedCurrent, m_DirectionCurrent);
				m_Position.y -= lengthdir_y(m_SpeedCurrent, m_DirectionCurrent);
		
				m_SpeedCurrent = 0;
			break;
	}
}

double PudgeEntity::getFacingDirection() { return m_DirectionCurrent; }
