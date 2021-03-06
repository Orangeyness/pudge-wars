#ifndef H_USER_INPUT_PROXY_
#define H_USER_INPUT_PROXY_

#include "core/helpers/GeometryHelper.h"
#include "pudge-wars/InputProxyInterface.h"

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
		void update(const ALLEGRO_KEYBOARD_STATE* keyboardState, const ALLEGRO_MOUSE_STATE* mouseState, const Vector2D& positionOffset);

		virtual bool hasMoveDirection();
		virtual bool hasHookTarget();
		virtual double moveDirection();
		virtual Vector2D hookTarget();
};

#endif
