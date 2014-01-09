#include "GameEntityInterface.h"

GameEntityInterface::GameEntityInterface()
{
	m_EntityId = GameEntityInterface::IdIndex++; 
}

EntityStatus GameEntityInterface::update()
{
	return ENTITY_ALIVE;
}

int GameEntityInterface::id()
{
	return m_EntityId;
}

int GameEntityInterface::IdIndex = 0;
