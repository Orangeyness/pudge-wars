#include "EntityPool.h"

EntityPool::~EntityPool()
{
	if (!empty()) clean();
}

void EntityPool::add(GameEntityInterface* entity)
{
	m_EntityList.push_front(entity);
}

void EntityPool::add(CollidableEntityInterface* entity)
{
	m_EntityList.push_front(entity);
	m_CollidableEntityMap[entity->id()] = entity;
}

void EntityPool::remove(GameEntityInterface* entity)
{
	m_EntityList.remove(entity);

	m_CollidableEntityMap.erase(entity->id());
}

std::unordered_map<int, CollidableEntityInterface*>::const_iterator EntityPool::collidableBegin()
{
	return m_CollidableEntityMap.cbegin();
}

std::unordered_map<int, CollidableEntityInterface*>::const_iterator EntityPool::collidableEnd()
{
	return m_CollidableEntityMap.cend();
}

int EntityPool::updateAll() 
{
	std::forward_list<GameEntityInterface*> delete_list;

	auto it = m_EntityList.begin();
	auto prevIt = m_EntityList.before_begin();

	int entityCount = 0;

	while (it != m_EntityList.end())
	{
		GameEntityInterface* currentEntity = *it;

		EntityStatus rtn = currentEntity->update();

		it ++;

		if (rtn == ENTITY_DEAD)
		{
			m_EntityList.erase_after(prevIt);
			m_CollidableEntityMap.erase(currentEntity->id());

			delete_list.push_front(currentEntity);
		}
		else
		{
			entityCount ++;
			prevIt ++;
		}
	}

	// Delete any dead entities after all entities 
	// have been updated.
	while(!delete_list.empty())
	{
		delete delete_list.front();
		delete_list.pop_front();
	}

	return entityCount;
}

void EntityPool::drawAll()
{
	auto it = m_EntityList.begin();

	while (it != m_EntityList.end())
	{
		GameEntityInterface* currentEntity = *it;
		currentEntity->draw();

		it ++;
	}
	
}

void EntityPool::clean()
{
	while(!m_EntityList.empty())
	{
		delete m_EntityList.front();
		m_EntityList.pop_front();
	}
}

bool EntityPool::empty()
{
	return m_EntityList.empty();
}
