#ifndef H_GAME_ENTITY_INTERFACE_
#define H_GAME_ENTITY_INTERFACE_

#include "GameConstants.h"
#include "GameException.h"

typedef bool EntityStatus;

#define ENTITY_ALIVE true
#define ENTITY_DEAD false
#define ENTITY_ID_NULL -1

class GameEntityInterface
{
	private:
		int m_EntityId;

	public:
		GameEntityInterface();
		virtual EntityStatus update();
		virtual void draw() = 0;
		virtual ~GameEntityInterface();

		virtual int id();

		static int AliveCount();
		static int TotalCount();
		static GameEntityInterface* GetAliveById(int id);

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
