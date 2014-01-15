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
#define HOOK_TAIL_ADJUST_PROPORTION 1
#define HOOK_TAIL_ADJUST_MAX 0.1

HookEntity::HookEntity(int parentId, Vector2D position, double direction, double speed, double maxDistance)
{
	MessageRouter::Instance()->registerListener(this, EVENT_TYPE_ENTITY);

	m_ParentId = parentId;
	m_Position = position;
	m_Direction = direction;
	m_Speed = speed;
	m_DistanceCurrent = 0;
	m_DistanceMax = maxDistance;
	m_Retracting = false;

	m_TailList.push_front(position);
}

HookEntity::~HookEntity()
{
	MessageRouter::Instance()->deregisterListener(this);
}

EntityStatus HookEntity::update()
{
	DEBUG_SHOW("DEBUG MAIN", "hook distance", std::to_string(m_DistanceCurrent));
	
	m_DistanceCurrent += m_Speed;

	m_Position.x += lengthdir_x(m_Speed, m_Direction);
	m_Position.y += lengthdir_y(m_Speed, m_Direction);

	MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_ENTITY_MOVE, new EntityPositionEventArgs(this, m_Position)));

	updateHookTail();

	if (m_DistanceCurrent >= m_DistanceMax)
	{
		m_Retracting = true;
		m_Solid = false;
	}

	if (m_Retracting)
	{
		Vector2D currentRetractPoint = m_TailList.front();

		if (m_Position.euclideanDist(currentRetractPoint) < m_Speed)
		{
			m_TailList.pop_front();
			
			if (m_TailList.empty())
			{
				MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_HOOK_DETACH, new EntityEventArgs(this)));

				return ENTITY_DEAD;
			}

			currentRetractPoint = m_TailList.front();
		}

		m_Direction = m_Position.directionToPoint(currentRetractPoint);
	}

	return ENTITY_ALIVE;
}

void HookEntity::updateHookTail()
{
	if (m_TailList.size() < 3) return;
	/*
	auto prevIter = m_TailList.begin();
	auto currentIter = prevIter++;
	auto nextIter = currentIter++;
	
	while (nextIter != m_TailList.end())
	{
		double avgX = (prevIter->x + nextIter->x) / 2;
		double avgY = (prevIter->y + nextIter->y) / 2;
	
		double xAdjust = std::min(HOOK_TAIL_ADJUST_MAX, 
			(avgX - currentIter->x) / HOOK_TAIL_ADJUST_PROPORTION);

		double yAdjust = std::min(HOOK_TAIL_ADJUST_MAX, 
			(avgY - currentIter->y) / HOOK_TAIL_ADJUST_PROPORTION);

		currentIter->x += xAdjust;
		currentIter->y += yAdjust;

		prevIter = currentIter;
		currentIter = nextIter++;
	}*/
}

void HookEntity::draw()
{
	al_draw_filled_circle(m_Position.x, m_Position.y, 5, al_map_rgb(0, 250, 0));

	Vector2D currentPoint = m_TailList.front();
	Vector2D prevPoint = m_Position;

	auto it = m_TailList.cbegin();
	while(it != m_TailList.cend())
	{
		al_draw_line(currentPoint.x, currentPoint.y, prevPoint.x, prevPoint.y, al_map_rgb(0, 200, 0), 1);

		it ++;
		prevPoint = currentPoint;
		currentPoint = *it;
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
				MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_HOOK_ATTACH, new DoubleEntityEventArgs(hookableEntity, this)));
			
				// Turn solid off, so the hook doesn't collide with anything else
				m_Solid = false;
				m_Retracting = true;
				break;
			}
	
			// Otherwise we're bouncing off the object
			CollidableEntityInterface* entity = args->getEntity<CollidableEntityInterface*>();

			// Calculate new direction
			m_Direction = CollisionChecker::calculateReflectAngle(entity, m_Position, m_Direction);

			// Add the bounce point to the tail list
			if (m_Position.sqauredEuclideanDist(m_TailList.front()) > DIST_MEASURE)
			{
				m_TailList.push_front(m_Position);
			}

			// Update position
			m_Position.x += lengthdir_x(m_Speed, m_Direction);
			m_Position.y += lengthdir_y(m_Speed, m_Direction);
			break;
		}

		case EVENT_TYPE_ENTITY_MOVE:
		{
			/*
				We want the hook chain to be connected to its parent pudge at all times
				so increase its tail when pudge moves.
			*/
			EntityPositionEventArgs* args = event.getArgs<EntityPositionEventArgs*>();

			if (args->getEntityId() == m_ParentId)
			{
				Vector2D newPosition = args->getPosition();

				if (newPosition.sqauredEuclideanDist(m_TailList.back()) > DIST_MEASURE)
				{
					m_DistanceCurrent += newPosition.euclideanDist(m_TailList.back());

					m_TailList.push_back(newPosition);
				}
			}

			break;
		}
		
	}
}
