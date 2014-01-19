#include "pudge-wars/pudge-states/PudgeStunRecoveryState.h"

PudgeStunRecoveryState::PudgeStunRecoveryState(int recoveryTime)
	: m_StunRecoveryTimeLeft(recoveryTime) { } 

EntityStatus PudgeStunRecoveryState::update(PudgeEntity& pudge)
{
	m_StunRecoveryTimeLeft --;

	if (m_StunRecoveryTimeLeft < 0) 
	{
		// Change State -> Walk
		
		changeState(new PudgeWalkState());
	}
	
	return ENTITY_ALIVE;
}

void PudgeStunRecoveryState::processEvent(PudgeEntity& pudge, const Event& event)
{			

}
