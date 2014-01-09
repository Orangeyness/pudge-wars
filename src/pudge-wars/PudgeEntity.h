#ifndef _PUDGE_ENTITY_
#define _PUDGE_ENTITY_

#include "../core/CollidableEntityInterface.h"

#include "InputProxyInterface.h"

class PudgeEntity : public CollidableEntityInterface
{
	private:
		InputProxyInterface* m_Input;
		Vector2D m_HookTarget;

		EntityStatus processEvents();

	public:
		PudgeEntity(InputProxyInterface* input);
		virtual EntityStatus update();
		virtual void draw();

};

#endif
