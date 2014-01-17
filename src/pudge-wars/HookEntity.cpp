#include "HookEntity.h"

#include "HookableInterface.h"

#include "../core/GameConstants.h"
#include "../core/GameException.h"
#include "../core/MessageRouter.h"
#include "../core/GameDebugWindow.h"
#include "../core/CollisionChecker.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define DIST_MEASURE SQRD(5)
#define HOOK_TAIL_POINTS_FRAME_INTERVAL 2

HookEntity::HookEntity(int parentId, Vector2D position, double direction, double radius, double speed, double maxDistance)
{
	MessageRouter::Instance()->registerListener(this, EVENT_TYPE_ENTITY);

	m_Position.moveInDirection(radius, direction);

	m_ParentId = parentId;
	m_Position = position;
	m_Direction = direction;
	m_Speed = speed;
	m_DistanceCurrent = 0;
	m_DistanceMax = maxDistance;
	m_Retracting = false;
	m_CasterPosition = position;
	m_CasterRadius = radius;
	m_FramesSinceSpawn = 0;
	m_HookAttached = false;

	m_TailList.push_front(m_CasterPosition);
}

HookEntity::~HookEntity()
{
	MessageRouter::Instance()->deregisterListener(this);
}

EntityStatus HookEntity::update()
{
	DEBUG_SHOW("DEBUG MAIN", "hook distance", std::to_string(m_DistanceCurrent));
	DEBUG_SHOW("DEBUG MAIN", "hook resolution", std::to_string(m_TailList.size()));

	m_FramesSinceSpawn += 1;

	if (m_DistanceCurrent >= m_DistanceMax)
	{
		m_Retracting = true;
	}

	if (!m_Retracting)
	{
		updateForwardHook();
	}
	else
	{
		EntityStatus returnValue = updateRetractingHook();

		if (returnValue == ENTITY_DEAD)
		{
			return ENTITY_DEAD;
		}
	}

	m_DistanceCurrent += m_Speed;
	m_Position.x += lengthdir_x(m_Speed, m_Direction);
	m_Position.y += lengthdir_y(m_Speed, m_Direction);
	MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_ENTITY_MOVE, new EntityPositionEventArgs(this, m_Position)));

	return ENTITY_ALIVE;
}

void HookEntity::updateForwardHook()
{
	if (m_FramesSinceSpawn % HOOK_TAIL_POINTS_FRAME_INTERVAL)
	{
		m_TailList.push_front(m_CasterPosition);
	}

	auto nextIter = m_TailList.begin();
	auto currentIter = nextIter++;
	
	// Update all but last point position
	while (nextIter != m_TailList.end())
	{
		double moveDirection = currentIter->directionToPoint(*nextIter);
		
		currentIter->moveInDirection(m_Speed, moveDirection);

		currentIter = nextIter++;
	}

	// Update last point posiiton
	double moveDirection = currentIter->directionToPoint(m_Position);
	currentIter->moveInDirection(m_Speed, moveDirection);
}

EntityStatus HookEntity::updateRetractingHook()
{
	if (!m_TailList.empty())
	{
		// If we still have a tail update it
		// and delete the nearest point if it is
		// within m_Speed distance of the caster.
		auto nextIter = m_TailList.begin();
		auto currentIter = nextIter++;
		
		// Update all but first point position
		while (nextIter != m_TailList.end())
		{
			double moveDirection = nextIter->directionToPoint(*currentIter);
			
			nextIter->moveInDirection(m_Speed, moveDirection);

			currentIter = nextIter++;
		}

		// Update first point position
		auto firstIter = m_TailList.begin();
		double moveDistance = firstIter->euclideanDist(m_CasterPosition) - m_CasterRadius;
		
		if (moveDistance < m_Speed)
		{
			// Remove if at caster
			m_TailList.pop_front();
		}
		else
		{
			double moveDirection = firstIter->directionToPoint(m_CasterPosition);
			firstIter->moveInDirection(m_Speed, moveDirection);
		}

		//Update the direction of the hook point
		m_Direction = m_Position.directionToPoint(m_TailList.back());
	}
	else
	{
		// If we don't have a tail, check if we're 
		// close enough to the caster to be considered
		// complete.
		double moveDistance = m_Position.euclideanDist(m_CasterPosition) - m_CasterRadius;
		if (moveDistance - m_Radius * 2 < m_Speed)
		{
			if (m_HookAttached)
			{
				MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_HOOK_DETACH, new EntityEventArgs(this)));
				m_HookAttached = false;
			}
		
			if (moveDistance < m_Speed)
			{
				return ENTITY_DEAD;
			}
		}

		//Otherwise update the direction of the hook point
		m_Direction = m_Position.directionToPoint(m_CasterPosition);
	}
	
	return ENTITY_ALIVE;
}

void HookEntity::draw()
{
	al_draw_filled_circle(m_Position.x, m_Position.y, 5, al_map_rgb(0, 250, 0));

	if (!m_TailList.empty())
	{
		auto nextIter = m_TailList.begin();
		auto currentIter = nextIter++;

		al_draw_line(currentIter->x, currentIter->y, m_CasterPosition.x, m_CasterPosition.y, al_map_rgb(0, 200, 0), 1);

		// Update all but last point position
		while (nextIter != m_TailList.end())
		{
			al_draw_line(currentIter->x, currentIter->y, nextIter->x, nextIter->y, al_map_rgb(0, 200, 0), 1);

			currentIter = nextIter ++;
		}

		al_draw_line(currentIter->x, currentIter->y, m_Position.x, m_Position.y, al_map_rgb(0, 200, 0), 1);
	}
	else
	{	
		al_draw_line(m_CasterPosition.x, m_CasterPosition.y, m_Position.x, m_Position.y, al_map_rgb(0, 200, 0), 1);
	}
}

void HookEntity::processEvent(const Event& event)
{
	switch(event.getType())
	{
		case EVENT_TYPE_COLLISION:
		{
			/*
				On collision check if entity is hookable or not, if the entity is hookable 
				generate a hook attach event with its id and and our id.

				Otherwise bounce off the object.
			*/
			EntityEventArgs* args = event.getArgs<EntityEventArgs*>();
				
			// Ensure we're not colliding with our parent pudge.
			if (args->getEntityId() == m_ParentId) break;

			// Check if hookable
			HookableInterface* hookableEntity = args->tryGetEntity<HookableInterface*>();
			if (hookableEntity)
			{
				MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_HOOK_ATTACH, new DoubleEntityPositionEventArgs(hookableEntity, this, m_Position)));
			
				// Turn solid off, so the hook doesn't collide with anything else
				m_HookAttached = true;
				m_Solid = false;
				m_Retracting = true;
				break;
			}
	
			// Otherwise we're bouncing off the object
			CollidableEntityInterface* entity = args->getEntity<CollidableEntityInterface*>();

			// Calculate new direction
			m_Direction = CollisionChecker::calculateReflectAngle(entity, m_Position, m_Direction);

			// Update position
			m_Position.x += lengthdir_x(m_Speed, m_Direction);
			m_Position.y += lengthdir_y(m_Speed, m_Direction);
			break;
		}

		case EVENT_TYPE_ENTITY_MOVE:
		{
			/*
				We need to keep track of the casters position so the hook chain
				will chain to the right position.
			*/
			EntityPositionEventArgs* args = event.getArgs<EntityPositionEventArgs*>();

			if (args->getEntityId() == m_ParentId)
			{
				m_CasterPosition = args->getPosition();
			}

			break;
		}
		
	}
}
