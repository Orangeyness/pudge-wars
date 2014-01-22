#ifndef H_ENTITY_
#define H_ENTITY_

#include "core/GameConstants.h"
#include "core/GameException.h"
#include "core/helpers/GeometryHelper.h"

typedef bool EntityStatus;

#define ENTITY_ALIVE true
#define ENTITY_DEAD false
#define ENTITY_ID_NULL -1

class Entity
{
	private:
		int m_EntityId;

	public:
		Entity();
		virtual EntityStatus update();
		virtual void draw(Rect viewWindow) = 0;
		virtual ~Entity();

		virtual int id();

		static int AliveCount();
		static int TotalCount();
		static Entity* GetAliveById(int id);

		template<typename T> 
		T toType()
		{
			T entity = dynamic_cast<T>(this);
			if (entity == NULL) THROW_GAME_EXCEPTION(EXCEP_UNEXPECTED_ENTITY_TYPE);

			return entity;
		}

		template<typename T> 
		T tryToType()
		{
			return dynamic_cast<T>(this);
		}
};



#endif
