#include "core/entities/Entity.h"

#include <unordered_map>

static int _EntityCount = 0;
static int _EntityIdCount = 0;
static std::unordered_map<int, Entity*> _EntityLookUp;

Entity::Entity()
{
	_EntityCount ++;
	m_EntityId = _EntityIdCount++; 

	_EntityLookUp[m_EntityId] = this;
}

Entity::~Entity()
{
	_EntityCount --;
	_EntityLookUp.erase(m_EntityId);
}

EntityStatus Entity::update()
{
	return ENTITY_ALIVE;
}

int Entity::id()
{
	return m_EntityId;
}

int Entity::AliveCount()
{
	return _EntityCount;
}

int Entity::TotalCount()
{
	return _EntityIdCount;
}

Entity* Entity::GetAliveById(int id)
{
	auto it = _EntityLookUp.find(id);
	
	if (it == _EntityLookUp.end()) 
		return NULL;

	return (*it).second;
}
