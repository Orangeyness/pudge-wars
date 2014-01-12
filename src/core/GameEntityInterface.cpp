#include "GameEntityInterface.h"

#include <unordered_map>

static int _EntityCount = 0;
static int _EntityIdCount = 0;
static std::unordered_map<int, GameEntityInterface*> _EntityLookUp;

GameEntityInterface::GameEntityInterface()
{
	_EntityCount ++;
	m_EntityId = _EntityIdCount++; 

	_EntityLookUp[m_EntityId] = this;
}

GameEntityInterface::~GameEntityInterface()
{
	_EntityCount --;
	_EntityLookUp.erase(m_EntityId);
}

EntityStatus GameEntityInterface::update()
{
	return ENTITY_ALIVE;
}

int GameEntityInterface::id()
{
	return m_EntityId;
}

int GameEntityInterface::AliveCount()
{
	return _EntityCount;
}

int GameEntityInterface::TotalCount()
{
	return _EntityIdCount;
}

GameEntityInterface* GameEntityInterface::GetAliveById(int id)
{
	auto it = _EntityLookUp.find(id);
	
	if (it == _EntityLookUp.end()) 
		return NULL;

	return (*it).second;
}
