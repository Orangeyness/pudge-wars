#include "pudge-wars/pudge-states/PudgeOnHookState.h"

PudgeOnHookState::PudgeOnHookState(PudgeEntity& pudge, const Vector2D& hookPosition) 
{
	m_HookOffset = pudge.m_Position - hookPosition;
	m_PositionPrevious = pudge.m_Position;
}

EntityStatus PudgeOnHookState::update(PudgeEntity& pudge)
{
	return ENTITY_ALIVE;
}

void PudgeOnHookState::processEvent(PudgeEntity& pudge, const Event& event)
{			
	if (event.getType() != EVENT_TYPE_COLLISION) return;
	
	pudge.m_Position = m_PositionPrevious;

	pudge.dettachHook();
}

void PudgeOnHookState::moveToHook(PudgeEntity& pudge, const Vector2D& hookPosition)
{
	m_PositionPrevious = pudge.m_Position;
	pudge.m_Position = hookPosition + m_HookOffset;
}

void PudgeOnHookState::dettachHook(PudgeEntity& pudge)
{
	changeState(new PudgeStunRecoveryState(pudge.m_HookedRecoveryTime));
}

void PudgeOnHookState::enter(PudgeEntity& pudge)
{
	pudge.m_SpeedCurrent = 0;

	pudge.removeCollisionGroup(COLLISION_GROUP_BASIC);
	pudge.removeCollisionGroup(COLLISION_GROUP_HOOKABLE);
	pudge.addCollisionGroup(COLLISION_GROUP_HOOKED);
}

void PudgeOnHookState::exit(PudgeEntity& pudge)
{
	pudge.addCollisionGroup(COLLISION_GROUP_BASIC);
	pudge.addCollisionGroup(COLLISION_GROUP_HOOKABLE);
	pudge.removeCollisionGroup(COLLISION_GROUP_HOOKED);
}
