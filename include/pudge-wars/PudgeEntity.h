#ifndef H_PUDGE_ENTITY_
#define H_PUDGE_ENTITY_

#include "core/entities/EntityRadial.h"

#include "pudge-wars/InputProxyInterface.h"
#include "pudge-wars/HookableInterface.h"

class PudgeEntity : public virtual EntityRadial, public virtual HookableInterface
{
	private:
		double m_DirectionCurrent;
		double m_DirectionTarget;
		double m_DirectionTurnRate;
		double m_SpeedCurrent;
		double m_SpeedMax;
		double m_SpeedAcceleration;
		double m_SpeedDeceleration;

		bool m_HookActive;
		bool m_HookRecoveryActive;
		int  m_HookRecoveryTime;
		int  m_HookRecoveryTimeLeft;
		bool m_IsHooked;


		InputProxyInterface* m_Input;
		Vector2D m_HookTarget;

		EntityStatus processEvents();

	public:
		PudgeEntity(InputProxyInterface* input, double x, double y);
		virtual EntityStatus update();
		virtual void draw();
		virtual void processEvent(const Event& event);

		virtual void moveToHook(const Vector2D& hookPosition);
		virtual void attachHook(int hookId, const Vector2D& hookPosition);
		virtual void dettachHook();

		double getFacingDirection();
};

#endif
