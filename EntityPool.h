#ifndef _ENTITY_POOL_
#define _ENTITY_POOL_

#include "GameEntityInterface.h"

#include <list>

class EntityPool
{
	private:
		std::list<GameEntityInterface*> m_EntityList;
		
	public:
		~EntityPool();
		
		void add(GameEntityInterface* entity);
		void remove(GameEntityInterface* entity);

		int updateAll();
		void drawAll();
		void clean();

		bool empty();
		int entityCount();
};


#endif
