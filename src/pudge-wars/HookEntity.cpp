#include "HookEntity.h"

#include "HookableInterface.h"

#include "../core/GameConstants.h"
#include "../core/GameException.h"
#include "../core/MessageRouter.h"
#include "../core/GameDebugWindow.h"
#include "../core/CollisionChecker.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

HookEntity::HookEntity(int parentId, Vector2D position, double direction, double speed, int life)
{
	MessageRouter::Instance()->registerListener(this, EVENT_TYPE_ENTITY);

	m_ParentId = parentId;
	m_Position = position;
	m_Direction = direction;
	m_Speed = speed;
	m_LifeRemaining = life;

	m_TailList.push_front(position);
}

HookEntity::~HookEntity()
{
	MessageRouter::Instance()->deregisterListener(this);
}

EntityStatus HookEntity::update()
{
	m_LifeRemaining --;

	m_Position.x -= lengthdir_x(m_Speed, m_Direction);
	m_Position.y -= lengthdir_y(m_Speed, m_Direction);

	MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_ENTITY_MOVE, new EntityPositionEventArgs(this, m_Position)));

	if (m_LifeRemaining > 0)
		return ENTITY_ALIVE;

	MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_HOOK_DETACH, new EntityEventArgs(this)));

	return ENTITY_DEAD;
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
			EntityEventArgs* args = dynamic_cast<EntityEventArgs*>(event.getArgs());
			if (args == NULL) THROW_GAME_EXCEPTION(EXCEP_EVENT_WRONG_ARGTYPE);
			if (args->getEntityId() == m_ParentId) break;

			HookableInterface* hookable = dynamic_cast<HookableInterface*>(args->getEntity());
			if (hookable != NULL)
			{
				MessageRouter::Instance()->broadcast(Event(EVENT_TYPE_HOOK_ATTACH, new DoubleEntityEventArgs(hookable, this)));
				m_Solid = false;
			}
			else
			{
				CollidableEntityInterface* entity = dynamic_cast<CollidableEntityInterface*>(args->getEntity());
				if (entity == NULL) THROW_GAME_EXCEPTION(EXCEP_UNEXPECTED_ENTITY_TYPE);

				m_Direction = CollisionChecker::calculateReflectAngle(entity, m_Position, m_Direction);

				if (m_Position.sqauredEuclideanDist(m_TailList.front()) > SQRD(20))
				{
					m_TailList.push_front(m_Position);
				}

				m_Position.x -= lengthdir_x(m_Speed, m_Direction);
				m_Position.y -= lengthdir_y(m_Speed, m_Direction);
			}

			break;
		}

		case EVENT_TYPE_ENTITY_MOVE:
		{
			EntityPositionEventArgs* args = dynamic_cast<EntityPositionEventArgs*>(event.getArgs());
			if (args == NULL) THROW_GAME_EXCEPTION(EXCEP_EVENT_WRONG_ARGTYPE);			

			if (args->getEntityId() == m_ParentId)
			{
				Vector2D newPosition = args->getPosition();

				if (newPosition.sqauredEuclideanDist(m_TailList.back()) > SQRD(20))
				{
					m_TailList.push_back(newPosition);
				}
			}

			break;
		}
		
	}
}
