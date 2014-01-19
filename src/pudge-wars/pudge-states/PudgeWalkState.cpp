#include "pudge-wars/pudge-states/PudgeWalkState.h"
#include "pudge-wars/pudge-states/PudgeHookThrowState.h"

EntityStatus PudgeWalkState::update(PudgeEntity& pudge)
{
	if (pudge.m_Input->hasMoveDirection())
	{
		pudge.m_DirectionTarget = pudge.m_Input->moveDirection();
		pudge.m_SpeedCurrent = std::min(pudge.m_SpeedCurrent + pudge.m_SpeedAcceleration, pudge.m_SpeedMax);
	}
	else
	{
		pudge.m_SpeedCurrent = std::max(pudge.m_SpeedCurrent - pudge.m_SpeedDeceleration, 0.0);
	}

	if (pudge.m_Input->hasHookTarget())
	{
		// Change State -> Hook Throw
		// Pudge is now aiming hook to throw
		changeState(new PudgeHookThrowState(pudge.m_Input->hookTarget()));
	}
	
	return ENTITY_ALIVE;
}

void PudgeWalkState::processEvent(PudgeEntity& pudge, const Event& event)
{			
	if (event.getType() != EVENT_TYPE_COLLISION) return;

	pudge.m_Position.x -= lengthdir_x(pudge.m_SpeedCurrent, pudge.m_DirectionCurrent);
	pudge.m_Position.y -= lengthdir_y(pudge.m_SpeedCurrent, pudge.m_DirectionCurrent);

	pudge.m_SpeedCurrent = 0;
}
