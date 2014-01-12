#ifndef H_INTRO_STATE_
#define H_INTRO_STATE_

#include "../core/GameStateInterface.h"
#include "../core/GameEntityInterface.h"
#include "../core/EntityPool.h"
#include "../core/MessageRouter.h"
#include "../core/GameEngine.h"
#include "../core/Observer.h"
#include "UserInputProxy.h"

class IntroState : public GameStateInterface, public Observer
{
	private:
		UserInputProxy m_UserInput;
		EntityPool m_EntityPool;
		MessageRouter m_MessageRouter;

	public:
		IntroState();
		virtual ~IntroState();

		virtual void pause();
		virtual void resume();
		
		virtual void update(GameEngine* game);
		void detectCollisions();

		virtual void draw(GameEngine* game);
		virtual void notify(const Event& event);
};

#endif
