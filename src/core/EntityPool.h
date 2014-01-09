#ifndef _ENTITY_POOL_
#define _ENTITY_POOL_

#include "GameEntityInterface.h"
#include "CollidableEntityInterface.h"

#include <forward_list>
#include <unordered_map>

class EntityPool
{
	private:
		std::forward_list<GameEntityInterface*> m_EntityList;
		std::unordered_map<int, CollidableEntityInterface*> m_CollidableEntityMap;		

	public:
		~EntityPool();
		
		void add(GameEntityInterface* entity);
		void add(CollidableEntityInterface* entity);
		void remove(GameEntityInterface* entity);

		std::unordered_map<int, CollidableEntityInterface*>::const_iterator collidableBegin();
		std::unordered_map<int, CollidableEntityInterface*>::const_iterator collidableEnd();

		int updateAll();
		void drawAll();
		void clean();

		bool empty();
};


#endif
