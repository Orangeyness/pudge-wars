#include "IntroState.h"
#include "PudgeEntity.h"

#include <allegro5/allegro.h>

IntroState::IntroState()
{
	m_EntityPool.add(new PudgeEntity(&m_UserInput));
}

IntroState::~IntroState()
{
}

void IntroState::pause() { }
void IntroState::resume() { }

void IntroState::update(GameEngine* game)
{
	ALLEGRO_KEYBOARD_STATE keyboardState;
	ALLEGRO_MOUSE_STATE mouseState;

	al_get_keyboard_state(&keyboardState);	
	al_get_mouse_state(&mouseState);

	m_UserInput.update(&keyboardState, &mouseState);
	m_EntityPool.updateAll();

	if (m_EntityPool.empty())
		game->quit();
}

void IntroState::draw(GameEngine* game)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));

	m_EntityPool.drawAll();
}

