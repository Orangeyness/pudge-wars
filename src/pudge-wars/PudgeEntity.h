#ifndef _PUDGE_ENTITY_
#define _PUDGE_ENTITY_

#include "../core/GameEntityInterface.h"

#include "InputProxyInterface.h"

class PudgeEntity : public GameEntityInterface
{
	private:
		InputProxyInterface* m_Input;
		Vector2D m_HookTarget;
		double x;
		double y;

	public:
		PudgeEntity(InputProxyInterface* input);
		virtual entityrtn_t update();
		virtual void draw();

};

#endif
