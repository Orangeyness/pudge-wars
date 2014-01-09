#ifndef _INPUT_PROXY_
#define _INPUT_PROXY_

#include "../core/GeometryHelper.h"

class InputProxyInterface
{
	public:
		virtual bool hasMoveDirection() = 0;
		virtual bool hasHookTarget() = 0;
		virtual Vector2D moveDirection() = 0;
		virtual Vector2D hookTarget() = 0;
};

#endif
