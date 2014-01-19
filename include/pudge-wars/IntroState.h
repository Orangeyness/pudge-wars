#ifndef H_INTRO_STATE_
#define H_INTRO_STATE_

#include "core/GameStateInterface.h"
#include "core/GameEngine.h"
#include "core/entities/Entity.h"
#include "core/entities/EntityManager.h"
#include "core/events/BufferedEventService.h"
#include "core/events/EventObserver.h"
#include "pudge-wars/UserInputProxy.h"

class IntroState : public GameStateInterface, public EventObserver
{
	private:
		UserInputProxy m_UserInput;
		UserInputProxy m_Temp;
		EntityManager m_EntityManager;
		BufferedEventService m_Events;

		void detectCollisions();
	public:
		IntroState();
		virtual ~IntroState();

		virtual void pause();
		virtual void resume();
		
		virtual void update(GameEngine* game);
		virtual void draw(GameEngine* game);
		virtual void processEvent(const Event& event);
};

#endif
