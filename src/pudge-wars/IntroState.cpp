#include "pudge-wars/IntroState.h"
#include "pudge-wars/PudgeEntity.h"
#include "pudge-wars/WallEntity.h"
#include "pudge-wars/BallEntity.h"
#include "pudge-wars/HookEntity.h"

#include "core/GameConstants.h"
#include "core/GameDebugWindow.h"
#include "core/GameException.h"
#include "core/services/ServiceLocator.h"
#include "core/helpers/GeometryHelper.h"
#include "core/helpers/CollisionHelper.h"
#include "core/events/Event.h"

#include <allegro5/allegro.h>
#include <iostream>

IntroState::IntroState()
{
	ServiceLocator::AddService(&m_Events);

	m_Events.addListener(this, EVENT_TYPE_SPAWN);

	m_EntityManager.add(new PudgeEntity(&m_UserInput));
	m_EntityManager.add(new BallEntity(Vector2D(350, 300), 15));
	m_EntityManager.add(new WallEntity(Vector2D(20, 20), 300, 50));
}

IntroState::~IntroState()
{
	m_EntityManager.clean();
	m_Events.removeListener(this);

	ServiceLocator::RemoveService(&m_Events);
}

void IntroState::pause() { }
void IntroState::resume() { }

void IntroState::processEvent(const Event& event)
{
	switch(event.getType())
	{
		case EVENT_TYPE_SPAWN_HOOK:
		{
			EntityEventArgs* args = event.getArgs<EntityEventArgs*>();
			PudgeEntity* pudga = args->getEntity<PudgeEntity*>();

			m_EntityManager.add(new HookEntity(pudga->id(), pudga->getPosition(), pudga->getFacingDirection(), pudga->getRadius(), 10, 1500));
			break;
		}
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
	m_EntityManager.updateAll();

	// Check for collisions of now updated objects
	detectCollisions();
	
	// Route messages from this frame
	m_Events.doRoute();

	// Delete dead entities
	m_EntityManager.deleteDead();

	DEBUG_SHOW("DEBUG MAIN", "Entities Alive", std::to_string(Entity::AliveCount()), 1);

	if (m_EntityManager.empty())
		game->quit();
}

void IntroState::detectCollisions()
{
	auto itA = m_EntityManager.collidableBegin();
	auto end = m_EntityManager.collidableEnd();
	while (itA != end)
	{
		EntityCollidable* colliderA = (*itA).second;

		if (colliderA->isSolid())
		{
			auto itB = itA;
			itB ++;
			while (itB != end)
			{
				EntityCollidable* colliderB = (*itB).second;

				if (colliderB->isSolid() &&
					(colliderA->getCollisionGroup() & colliderB->getCollisionGroup()) != 0 &&
					CollisionHelper::isColliding(colliderA, colliderB))
				{
					m_Events.directMessage(colliderA, Event(EVENT_TYPE_COLLISION, new EntityEventArgs(colliderB)));
					m_Events.directMessage(colliderB, Event(EVENT_TYPE_COLLISION, new EntityEventArgs(colliderA)));
				}

				itB ++;
			}
		}

		itA ++;
	}
}

void IntroState::draw(GameEngine* game)
{
	al_clear_to_color(al_map_rgb(255, 255, 255));

	m_EntityManager.drawAll();
}

