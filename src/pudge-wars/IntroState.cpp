#include "IntroState.h"
#include "PudgeEntity.h"
#include "WallEntity.h"
#include "BallEntity.h"

#include "../core/GameConstants.h"
#include "../core/GameDebugWindow.h"
#include "../core/GeometryHelper.h"
#include "../core/CollisionChecker.h"
#include "../core/EventWithEntity.h"

#include <allegro5/allegro.h>

IntroState::IntroState()
{
	m_EntityPool.add(new PudgeEntity(&m_UserInput));
	m_EntityPool.add(new BallEntity(Vector2D(350, 300), 15));
	m_EntityPool.add(new WallEntity(Vector2D(20, 20), 300, 50));
}

IntroState::~IntroState()
{
}

void IntroState::pause() { }
void IntroState::resume() { }

void IntroState::update(GameEngine* game)
{
	// Handel Input
	ALLEGRO_KEYBOARD_STATE keyboardState;
	ALLEGRO_MOUSE_STATE mouseState;

	al_get_keyboard_state(&keyboardState);	
	al_get_mouse_state(&mouseState);

	m_UserInput.update(&keyboardState, &mouseState);

	// Detect Collisions
	auto itA = m_EntityPool.collidableBegin();
	auto end = m_EntityPool.collidableEnd();
	while (itA != end)
	{
		CollidableEntityInterface* colliderA = (*itA).second;

		auto itB = itA;
		itB ++;
		while (itB != end)
		{
			CollidableEntityInterface* colliderB = (*itB).second;
	
			if (CollisionChecker::isColliding(colliderA, colliderB))
			{
				colliderA->notify(new EventWithEntity(EVENT_TYPE_COLLISION, colliderB));
				colliderB->notify(new EventWithEntity(EVENT_TYPE_COLLISION, colliderA));
			}

			itB ++;
		}

		itA ++;
	}

	// Update all entities
	m_EntityPool.updateAll();

	DEBUG_SHOW("DEBUG MAIN", "Entities Alive", std::to_string(GameEntityInterface::AliveCount()), 1);

	if (m_EntityPool.empty())
		game->quit();
}

void IntroState::draw(GameEngine* game)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));

	m_EntityPool.drawAll();
}

