#ifndef _INTRO_STATE_
#define _INTRO_STATE_

#include "GameStateInterface.h"
#include "GameEngine.h"

class IntroState : public GameStateInterface
{
	private:
		int x;
		int y;

	public:
		IntroState();
		virtual ~IntroState();

		virtual void pause();
		virtual void resume();
		
		virtual void update(GameEngine* game);
		virtual void draw(GameEngine* game);
};

#endif
