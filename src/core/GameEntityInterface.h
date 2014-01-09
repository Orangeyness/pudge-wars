#ifndef _GAME_ENTITY_INTERFACE_
#define _GAME_ENTITY_INTERFACE_

typedef bool EntityStatus;

#define ENTITY_ALIVE true
#define ENTITY_DEAD false

class GameEntityInterface
{
	private:
		int m_EntityId;

	public:
		GameEntityInterface();
		virtual EntityStatus update();
		virtual void draw() = 0;
		virtual ~GameEntityInterface() {}

		virtual int id();

		static int IdIndex;
		
};



#endif
