#ifndef H_INPUT_PROXY_
#define H_INPUT_PROXY_

#include "core/helpers/GeometryHelper.h"

class InputProxyInterface
{
	public:
		virtual bool hasMoveDirection() = 0;
		virtual bool hasHookTarget() = 0;
		virtual double moveDirection() = 0;
		virtual Vector2D hookTarget() = 0;
};

#endif
