#include "IntroState.h"
#include "PudgeEntity.h"

#include <allegro5/allegro.h>

IntroState::IntroState()
{
	m_EntityPool.add(new PudgeEntity());
}

IntroState::~IntroState()
{
}

void IntroState::pause() { }
void IntroState::resume() { }

void IntroState::update(GameEngine* game)
{
	m_EntityPool.updateAll();
}

void IntroState::draw(GameEngine* game)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));

	m_EntityPool.drawAll();
}

