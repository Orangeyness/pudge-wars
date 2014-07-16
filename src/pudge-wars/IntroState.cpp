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

ALLEGRO_BITMAP* grass = NULL;
ALLEGRO_BITMAP* blendSet = NULL;
ALLEGRO_BITMAP* blendSetParts[66];

IntroState::IntroState()
	: m_Assets(ASSET_BASE_DIRECTORY)
{
	ServiceLocator::AddService(&m_Assets);
	ServiceLocator::AddService(&m_Events);

	m_Events.addListener(this, EVENT_TYPE_SPAWN);

	PudgeEntity* player = new PudgeEntity(&m_UserInput, 200, 200);

	m_EntityManager.add(player);
	m_EntityManager.add(new PudgeEntity(&m_Temp, 250, 250));
	m_EntityManager.add(new BallEntity(Vector2D(350, 300), 15));
	m_EntityManager.add(new WallEntity(Vector2D(20, 20), 300, 50));

	m_ViewPort.init(player, player->getPosition(), Vector2D(1000, 1000));

	loadAssets();
}

void IntroState::loadAssets()
{
	grass = ServiceLocator::GetAssetService()->loadBitmap("tiles/grass.png");
	blendSet = ServiceLocator::GetAssetService()->loadBitmap("tiles/blend_set.png");

	const int subWidth = 128;
	const int subHeight = 96;

	int currentIndex = 0;
	int currentRow = 0;
	for (; currentRow < 5; currentRow ++)
	{
		for (int currentColumn = 0; currentColumn < 8; currentColumn ++)
		{
			blendSetParts[currentIndex++] = al_create_sub_bitmap(blendSet, 
				currentColumn * subWidth, currentRow * subHeight, subWidth, subHeight);
		}
	}

	for (; currentRow < 6; currentRow ++)
	{
		for (int currentColumn = 0; currentColumn < 6; currentColumn ++)
		{
			blendSetParts[currentIndex++] = al_create_sub_bitmap(blendSet, 
				currentColumn * subWidth, currentRow * subHeight, subWidth, subHeight);
		}
	}

	for (; currentRow < 11; currentRow ++)
	{
		for (int currentColumn = 0; currentColumn < 4; currentColumn ++)
		{
			blendSetParts[currentIndex++] = al_create_sub_bitmap(blendSet, 
				currentColumn * subWidth, currentRow * subHeight, subWidth, subHeight);
		}
	}

	std::cout << currentIndex << std::endl;
}

void IntroState::destroyAssets()
{
	for (int i = 0; i < 50; i++)
	{
		al_destroy_bitmap(blendSetParts[i]);
	}
}

IntroState::~IntroState()
{
	m_EntityManager.clean();
	m_Events.removeListener(this);

	destroyAssets();

	ServiceLocator::RemoveService(&m_Events);
	ServiceLocator::RemoveService(&m_Assets);
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

	m_UserInput.update(&keyboardState, &mouseState, m_ViewPort.position());

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

	Rect viewWindow = m_ViewPort.get();

	ALLEGRO_STATE state;
	al_store_state(&state, ALLEGRO_STATE_ALL);
	/*al_hold_bitmap_drawing(true);
	for (int x = 0; x < viewWindow.width; x += al_get_bitmap_width(grass))
	{
		for (int y = 0; y < viewWindow.height; y += al_get_bitmap_height(grass))
		{
			al_draw_bitmap(grass, x - viewWindow.x, y - viewWindow.y, 0);
		}
	}
	al_hold_bitmap_drawing(false);
	*/

	int blendIndex = 1;
	ALLEGRO_BITMAP* blended = al_create_bitmap(
		al_get_bitmap_width(blendSetParts[blendIndex]),
		al_get_bitmap_height(blendSetParts[blendIndex])
		);

	al_set_target_bitmap(blended);

	al_clear_to_color(al_map_rgba(0, 0, 0, 0));
	al_draw_bitmap(blendSetParts[5], 0, 0, 0);
	al_set_separate_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ADD, ALLEGRO_ZERO, ALLEGRO_ONE);
	al_draw_bitmap(grass, 0, 0, 0);

	al_restore_state(&state);

	al_draw_bitmap(blended, 0, 0, 0);

	al_destroy_bitmap(blended);

	m_EntityManager.drawAll(viewWindow);
}

