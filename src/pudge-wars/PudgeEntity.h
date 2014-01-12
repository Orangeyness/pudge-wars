#ifndef H_PUDGE_ENTITY_
#define H_PUDGE_ENTITY_

#include "../core/RadialEntityInterface.h"

#include "InputProxyInterface.h"

class PudgeEntity : public RadialEntityInterface
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

		InputProxyInterface* m_Input;
		Vector2D m_HookTarget;

		EntityStatus processEvents();

	public:
		PudgeEntity(InputProxyInterface* input);
		virtual EntityStatus update();
		virtual void draw();

};

#endif
