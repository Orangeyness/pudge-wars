#ifndef H_ENTITY_MANAGER_
#define H_ENTITY_MANAGER_

#include "core/entities/Entity.h"
#include "core/entities/EntityCollidable.h"

#include <forward_list>
#include <unordered_map>

class EntityManager
{
	private:
		std::forward_list<Entity*> m_EntityList;
		std::forward_list<Entity*> m_EntityDeadList;
		std::unordered_map<int, EntityCollidable*> m_CollidableEntityMap;		

	public:
		~EntityManager();
		
		void add(Entity* entity);
		void add(EntityCollidable* entity);
		void remove(Entity* entity);

		std::unordered_map<int, EntityCollidable*>::const_iterator collidableBegin();
		std::unordered_map<int, EntityCollidable*>::const_iterator collidableEnd();

		int updateAll();
		void drawAll();
		void deleteDead();
		void clean();

		bool empty();
};


#endif
