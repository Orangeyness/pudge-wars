#ifndef H_PUDGE_HOOK_THROW_STATE_
#define H_PUDGE_HOOK_THROW_STATE_

#include "pudge-wars/pudge-states/PudgeState.h"

#include "core/helpers/GeometryHelper.h"

class PudgeHookThrowState : public PudgeState
{
	private:
		Vector2D m_HookTarget;

	public:
		PudgeHookThrowState(const Vector2D& target);
		virtual EntityStatus update(PudgeEntity& pudge);
		virtual void processEvent(PudgeEntity& pudge, const Event& event);
};

#endif
