#include "IntroState.h"
#include "PudgeEntity.h"
#include "WallEntity.h"
#include "BallEntity.h"
#include "HookEntity.h"

#include "../core/GameConstants.h"
#include "../core/GameDebugWindow.h"
#include "../core/GameException.h"
#include "../core/GeometryHelper.h"
#include "../core/CollisionChecker.h"
#include "../core/Event.h"

#include <allegro5/allegro.h>
#include <iostream>

IntroState::IntroState()
{
	m_MessageRouter.registerListener(this, EVENT_TYPE_SPAWN);

	m_EntityPool.add(new PudgeEntity(&m_UserInput));
	m_EntityPool.add(new BallEntity(Vector2D(350, 300), 15));
	m_EntityPool.add(new WallEntity(Vector2D(20, 20), 300, 50));
}

IntroState::~IntroState()
{
	m_MessageRouter.deregisterListener(this);
}

void IntroState::pause() { }
void IntroState::resume() { }

void IntroState::notify(const Event& event)
{
	switch(event.getType())
	{

		case EVENT_TYPE_SPAWN_HOOK:
			EntityEventArgs* args = dynamic_cast<EntityEventArgs*>(event.getArgs());

			if (args == NULL) 
				throw GameException(EXCEP_EVENT_WRONG_ARGTYPE);			

			PudgeEntity* pudga = dynamic_cast<PudgeEntity*>(args->getEntity());

			if (pudga == NULL)
				throw GameException(EXCEP_UNEXPECTED_ENTITY_TYPE);

			m_EntityPool.add(new HookEntity(pudga->getPosition(), pudga->getFacingDirection(), -10, 120));
		break;
	}
}

void IntroState::update(GameEngine* game)
{
	// Handel Input
	ALLEGRO_KEYBOARD_STATE keyboardState;
	ALLEGRO_MOUSE_STATE mouseState;

	al_get_keyboard_state(&keyboardState);	
	al_get_mouse_state(&mouseState);

	m_UserInput.update(&keyboardState, &mouseState);

	// Update all entities
	m_EntityPool.updateAll();

	// Check for collisions of now updated objects
	detectCollisions();
	
	// Route messages from this frame
	m_MessageRouter.doRoute();

	// Delete dead entities
	m_EntityPool.deleteDead();

	DEBUG_SHOW("DEBUG MAIN", "Entities Alive", std::to_string(GameEntityInterface::AliveCount()), 1);

	if (m_EntityPool.empty())
		game->quit();
}

void IntroState::detectCollisions()
{
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
				m_MessageRouter.directMessage(colliderA, Event(EVENT_TYPE_COLLISION));
				m_MessageRouter.directMessage(colliderB, Event(EVENT_TYPE_COLLISION));
			}

			itB ++;
		}

		itA ++;
	}
}

void IntroState::draw(GameEngine* game)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));

	m_EntityPool.drawAll();
}

