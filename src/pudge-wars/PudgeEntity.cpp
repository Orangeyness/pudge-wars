#include "pudge-wars/PudgeEntity.h"

#include "core/GameConstants.h"
#include "core/GameException.h"
#include "core/services/ServiceLocator.h"
#include "core/helpers/GeometryHelper.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <algorithm>

PudgeEntity::PudgeEntity(InputProxyInterface* input, double x, double y) 
{
	m_Input = input;	
	m_Radius = 20;
	m_Position.set(x, y);

	m_DirectionCurrent = 0;
	m_DirectionTarget = m_DirectionCurrent;
	m_DirectionTurnRate = DEG_TO_RAD(20);
	m_SpeedCurrent = 0;
	m_SpeedMax = 4;
	m_SpeedAcceleration = 0.5;
	m_SpeedDeceleration = 2;

	m_HookRecoveryTime = 20;
	m_HookedRecoveryTime = 50;
	
	m_State = new PudgeWalkState();

	addCollisionGroup(COLLISION_GROUP_PUDGES);
	addCollisionGroup(COLLISION_GROUP_HOOKABLE);
}

PudgeEntity::~PudgeEntity()
{
	cleanState();
}

EntityStatus PudgeEntity::update()
{
	if (m_State->readyToChangeState())
	{
		changeState(m_State->nextState());
	}

	EntityStatus rtn = m_State->update(*this);

	updateDirection();
	updatePosition();

	return rtn;
}

void PudgeEntity::updateDirection()
{
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
}

void PudgeEntity::updatePosition()
{
	if (m_SpeedCurrent > 0)
	{
		m_Position.x += lengthdir_x(m_SpeedCurrent, m_DirectionCurrent);
		m_Position.y += lengthdir_y(m_SpeedCurrent, m_DirectionCurrent);

		ServiceLocator::GetEventService()->broadcast(Event(EVENT_TYPE_ENTITY_MOVE, new EntityPositionEventArgs(this, m_Position)));
	}
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
	m_State->processEvent(*this, event);
}

void PudgeEntity::changeState(PudgeState* state)
{
	m_State->exit(*this);
	delete m_State;

	m_State = state;
	m_State->enter(*this);
}

void PudgeEntity::cleanState() 
{
	delete m_State;
	m_State = NULL;
}

void PudgeEntity::moveToHook(const Vector2D& hookPosition)
{
	m_State->moveToHook(*this, hookPosition);
}

void PudgeEntity::attachHook(int hookId, const Vector2D& hookPosition)
{
	HookableInterface::attachHook(hookId, hookPosition);

	m_State->attachHook(*this, hookId, hookPosition);
}

void PudgeEntity::dettachHook()
{
	HookableInterface::dettachHook();

	m_State->dettachHook(*this);
}

double PudgeEntity::getFacingDirection() { return m_DirectionCurrent; }
