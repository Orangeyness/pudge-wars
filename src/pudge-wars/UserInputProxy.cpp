#include "UserInputProxy.h"

UserInputProxy::UserInputProxy()
{
	m_LeftMouseDown = false;
	m_HasHookTarget = false;
}

void UserInputProxy::update(const ALLEGRO_KEYBOARD_STATE* keyboardState, const ALLEGRO_MOUSE_STATE* mouseState)
{
	m_MoveDirection.set(0, 0);

	if (al_key_down(keyboardState, ALLEGRO_KEY_A) || 
		al_key_down(keyboardState, ALLEGRO_KEY_LEFT))
	{
		m_MoveDirection.x -= 1;
	}	

	if (al_key_down(keyboardState, ALLEGRO_KEY_D) || 
		al_key_down(keyboardState, ALLEGRO_KEY_RIGHT))
	{
		m_MoveDirection.x += 1;
	}	

	if (al_key_down(keyboardState, ALLEGRO_KEY_W) || 
		al_key_down(keyboardState, ALLEGRO_KEY_UP))
	{
		m_MoveDirection.y -= 1;
	}	

	if (al_key_down(keyboardState, ALLEGRO_KEY_S) || 
		al_key_down(keyboardState, ALLEGRO_KEY_DOWN))
	{
		m_MoveDirection.y += 1;
	}	

	m_MoveDirection.normalise();

	m_HasHookTarget = false;
	if (mouseState->buttons & 1)
	{
		m_LeftMouseDown = true;
		m_HookTarget.set(mouseState->x, mouseState->y);
	}
		else if (m_LeftMouseDown)
	{
		m_LeftMouseDown = false;
		m_HasHookTarget = true;
	}
}

bool UserInputProxy::hasMoveDirection()
{
	return m_MoveDirection.magnitude() > 0;
}

bool UserInputProxy::hasHookTarget()
{
	return m_HasHookTarget;
}

Vector2D UserInputProxy::moveDirection()
{
	return m_MoveDirection;
}

Vector2D UserInputProxy::hookTarget()
{
	return m_HookTarget;
}
