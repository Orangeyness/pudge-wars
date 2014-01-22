#include "core/entities/EntityManager.h"

EntityManager::~EntityManager()
{
	if (!empty()) clean();
}

void EntityManager::add(Entity* entity)
{
	m_EntityList.push_front(entity);
}

void EntityManager::add(EntityCollidable* entity)
{
	m_EntityList.push_front(entity);
	m_CollidableEntityMap[entity->id()] = entity;
}

void EntityManager::remove(Entity* entity)
{
	m_EntityList.remove(entity);

	m_CollidableEntityMap.erase(entity->id());
}

std::unordered_map<int, EntityCollidable*>::const_iterator EntityManager::collidableBegin()
{
	return m_CollidableEntityMap.cbegin();
}

std::unordered_map<int, EntityCollidable*>::const_iterator EntityManager::collidableEnd()
{
	return m_CollidableEntityMap.cend();
}

int EntityManager::updateAll() 
{
	auto it = m_EntityList.begin();
	auto prevIt = m_EntityList.before_begin();

	int entityCount = 0;

	while (it != m_EntityList.end())
	{
		Entity* currentEntity = *it;

		EntityStatus rtn = currentEntity->update();

		it ++;

		if (rtn == ENTITY_DEAD)
		{
			m_EntityList.erase_after(prevIt);
			m_CollidableEntityMap.erase(currentEntity->id());

			m_EntityDeadList.push_front(currentEntity);
		}
		else
		{
			entityCount ++;
			prevIt ++;
		}
	}

	return entityCount;
}

void EntityManager::deleteDead()
{
	// Delete any dead entities after all entities 
	// have been updated.
	while(!m_EntityDeadList.empty())
	{
		delete m_EntityDeadList.front();
		m_EntityDeadList.pop_front();
	}
}

void EntityManager::drawAll(Rect viewWindow)
{
	auto it = m_EntityList.begin();

	while (it != m_EntityList.end())
	{
		Entity* currentEntity = *it;
		currentEntity->draw(viewWindow);

		it ++;
	}
	
}

void EntityManager::clean()
{
	while(!m_EntityList.empty())
	{
		delete m_EntityList.front();
		m_EntityList.pop_front();
	}
}

bool EntityManager::empty()
{
	return m_EntityList.empty();
}
