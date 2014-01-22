#ifndef H_PUDGE_ENTITY_
#define H_PUDGE_ENTITY_

#include "core/entities/EntityRadial.h"

#include "pudge-wars/InputProxyInterface.h"
#include "pudge-wars/HookableInterface.h"


//State forward declarations
class PudgeState;
class PudgeWalkState;
class PudgeHookThrowState;
class PudgeStunRecoveryState;
class PudgeOnHookState;

class PudgeEntity : public virtual EntityRadial, public virtual HookableInterface
{
	friend class PudgeWalkState;
	friend class PudgeHookThrowState;
	friend class PudgeStunRecoveryState;
	friend class PudgeOnHookState;

	private:
		InputProxyInterface* m_Input;
		PudgeState* m_State;	

	protected:
		double m_DirectionCurrent;
		double m_DirectionTarget;
		double m_DirectionTurnRate;
		double m_SpeedCurrent;
		double m_SpeedMax;
		double m_SpeedAcceleration;
		double m_SpeedDeceleration;
		int  m_HookRecoveryTime;
		int  m_HookedRecoveryTime;

		void updateDirection();
		void updatePosition();

		void changeState(PudgeState* state);
		void cleanState();

	public:
		PudgeEntity(InputProxyInterface* input, double x, double y);
		~PudgeEntity();
		virtual EntityStatus update();
		virtual void draw(Rect viewWindow);
		virtual void processEvent(const Event& event);

		virtual void moveToHook(const Vector2D& hookPosition);
		virtual void attachHook(int hookId, const Vector2D& hookPosition);
		virtual void dettachHook();

		double getFacingDirection();
};

//State includes
#include "pudge-wars/pudge-states/PudgeState.h"
#include "pudge-wars/pudge-states/PudgeWalkState.h"
#include "pudge-wars/pudge-states/PudgeHookThrowState.h"
#include "pudge-wars/pudge-states/PudgeStunRecoveryState.h"
#include "pudge-wars/pudge-states/PudgeOnHookState.h"

#endif
