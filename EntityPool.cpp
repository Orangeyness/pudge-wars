#include "EntityPool.h"

EntityPool::~EntityPool()
{
	if (!empty()) clean();
}

void EntityPool::add(GameEntityInterface* entity)
{
	m_EntityList.push_back(entity);
}

void EntityPool::remove(GameEntityInterface* entity)
{
	m_EntityList.remove(entity);
}

int EntityPool::updateAll() 
{
	auto it = m_EntityList.begin();

	while (it != m_EntityList.end())
	{
		GameEntityInterface* currentEntity = *it;

		entityrtn_t rtn = currentEntity->update();

		if (rtn == ENTITY_DELETE)
		{
			delete currentEntity;
			it = m_EntityList.erase(it);
		}
		else
		{
			it ++;
		}
	}

	return m_EntityList.size();
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

int EntityPool::entityCount()
{
	return m_EntityList.size();
}
