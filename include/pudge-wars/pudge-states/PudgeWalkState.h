#ifndef H_PUDGE_WALK_STATE
#define H_PUDGE_WALK_STATE

#include "pudge-wars/pudge-states/PudgeState.h"

class PudgeWalkState : public PudgeState
{
	public:
		virtual EntityStatus update(PudgeEntity& pudge);
		virtual void processEvent(PudgeEntity& pudge, const Event& event);
};

#endif
