#ifndef _INTRO_STATE_
#define _INTRO_STATE_

#include "GameStateInterface.h"
#include "GameEntityInterface.h"
#include "UserInputProxy.h"
#include "EntityPool.h"
#include "GameEngine.h"

class IntroState : public GameStateInterface
{
	private:
		UserInputProxy m_UserInput;
		EntityPool m_EntityPool;

	public:
		IntroState();
		virtual ~IntroState();

		virtual void pause();
		virtual void resume();
		
		virtual void update(GameEngine* game);
		virtual void draw(GameEngine* game);
};

#endif
