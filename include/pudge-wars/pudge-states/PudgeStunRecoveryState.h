#ifndef H_PUDGE_STUN_RECOVERY_STATE_
#define H_PUDGE_STUN_RECOVERY_STATE_

#include "pudge-wars/pudge-states/PudgeState.h"

class PudgeStunRecoveryState : public PudgeState
{
	private:
		int  m_StunRecoveryTimeLeft;

	public:
		PudgeStunRecoveryState(int recoveryTime);
		virtual EntityStatus update(PudgeEntity& pudge);
		virtual void processEvent(PudgeEntity& pudge, const Event& event);
};

#endif
