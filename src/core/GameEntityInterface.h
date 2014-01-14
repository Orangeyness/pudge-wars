#ifndef H_GAME_ENTITY_INTERFACE_
#define H_GAME_ENTITY_INTERFACE_


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
};



#endif
