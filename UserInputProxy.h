#ifndef _USER_INPUT_PROXY_
#define _USER_INPUT_PROXY_

#include "InputProxyInterface.h"
#include "GeometryHelper.h"

#include <allegro5/allegro.h>

class UserInputProxy : public InputProxyInterface
{
	private:
		bool m_LeftMouseDown;
		Vector2D m_HookTarget;
		Vector2D m_MoveDirection;
		bool m_HasHookTarget;

	public:
		UserInputProxy();
		void update(const ALLEGRO_KEYBOARD_STATE* keyboardState, const ALLEGRO_MOUSE_STATE* mouseState);

		virtual bool hasMoveDirection();
		virtual bool hasHookTarget();
		virtual Vector2D moveDirection();
		virtual Vector2D hookTarget();
};


#endif
