#ifndef H_PUDGE_STATE_
#define H_PUDGE_STATE_

#include "core/entities/Entity.h"
#include "core/events/Event.h"

class PudgeEntity;

class PudgeState
{
	protected:
		PudgeState* m_NextState;

	public:
		PudgeState();
		virtual ~PudgeState();

		virtual EntityStatus update(PudgeEntity& pudge) = 0;
		virtual void processEvent(PudgeEntity& pudge, const Event& event) = 0;
		virtual void enter(PudgeEntity& pudge);
		virtual void exit(PudgeEntity& pudge);
		virtual void moveToHook(PudgeEntity& pudge, const Vector2D& hookPosition);
		virtual void attachHook(PudgeEntity& pudge, int hookId, const Vector2D& hookPosition);
		virtual void dettachHook(PudgeEntity& pudge);

		bool readyToChangeState();
		void changeState(PudgeState* next);
		PudgeState* nextState();
};

#include "pudge-wars/PudgeEntity.h"

#endif
