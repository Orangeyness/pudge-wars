#ifndef H_PUDGE_ON_HOOK_STATE
#define H_PUDGE_ON_HOOK_STATE

#include "pudge-wars/pudge-states/PudgeState.h"

#include "core/helpers/GeometryHelper.h"

class PudgeOnHookState : public PudgeState
{
	private:
		Vector2D m_HookOffset;
		Vector2D m_PositionPrevious;

	public:
		PudgeOnHookState(PudgeEntity& pudge, const Vector2D& hookPosition);
		virtual EntityStatus update(PudgeEntity& pudge);
		virtual void processEvent(PudgeEntity& pudge, const Event& event);
		virtual void enter(PudgeEntity& pudge);
		virtual void exit(PudgeEntity& pudge);
		virtual void moveToHook(PudgeEntity& pudge, const Vector2D& hookPosition);
		virtual void dettachHook(PudgeEntity& pudge);
};

#endif
