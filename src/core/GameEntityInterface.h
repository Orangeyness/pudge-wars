#ifndef _GAME_ENTITY_INTERFACE_
#define _GAME_ENTITY_INTERFACE_

typedef bool entityrtn_t;

#define ENTITY_KEEP true
#define ENTITY_DELETE false

class GameEntityInterface
{
	public:
		virtual entityrtn_t update() { return ENTITY_KEEP; }
		virtual void draw() = 0;
		virtual ~GameEntityInterface() {}
};



#endif
