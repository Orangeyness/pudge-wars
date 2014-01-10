#ifndef H_GAME_STATE_INTERFACE_
#define H_GAME_STATE_INTERFACE_

class GameEngine;

class GameStateInterface
{
	public:
		virtual void pause() = 0;
		virtual void resume() = 0;
		
		virtual void update(GameEngine* game) = 0;
		virtual void draw(GameEngine* game) = 0;
		virtual ~GameStateInterface() {}
};

#endif
