#include "pudge-wars/pudge-states/PudgeHookThrowState.h"

#include "core/services/ServiceLocator.h"

PudgeHookThrowState::PudgeHookThrowState(const Vector2D& target)
	: m_HookTarget(target) { }

EntityStatus PudgeHookThrowState::update(PudgeEntity& pudge)
{
	if (pudge.m_Input->hasHookTarget())
	{
		m_HookTarget = pudge.m_Input->hookTarget();

	}

	pudge.m_SpeedCurrent = 0;
	pudge.m_DirectionTarget = pudge.m_Position.directionToPoint(m_HookTarget);

	if (pudge.m_DirectionCurrent == pudge.m_DirectionTarget)
	{
		ServiceLocator::GetEventService()->broadcast(Event(EVENT_TYPE_SPAWN_HOOK, new EntityEventArgs(&pudge)));

		// Change State -> Stun Recovery
		changeState(new PudgeStunRecoveryState(pudge.m_HookRecoveryTime));
	}
	
	return ENTITY_ALIVE;
}

void PudgeHookThrowState::processEvent(PudgeEntity& pudge, const Event& event)
{			

}
