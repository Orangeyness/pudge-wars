#include "GameEngine.h"
#include "GameException.h"

GameEngine::GameEngine()
{
	// Settings
	m_TargetFramesPerSecond = 60;
	
	// State
	m_FrameCount = 0;
	m_GameActive = false;

	// Allegro Engine
	m_Display = NULL;
	m_EventQueue = NULL;
	m_Timer = NULL;
}

GameEngine::~GameEngine()
{
	// Cleanup allegro engine objects
	if (m_Timer) al_destroy_timer(m_Timer);
	if (m_Display) al_destroy_display(m_Display);
	if (m_EventQueue) al_destroy_event_queue(m_EventQueue);

	// Cleanup State stack
	while(m_StateStack.empty())
	{
		delete m_StateStack.top();
		m_StateStack.pop();
	}
}

void GameEngine::initialise()
{
	if (!al_init())
	{
		throw GameException(EXCEP_ALLEG_ENGINE_FAILED);
	}	

	m_Display = al_create_display(640, 480);
	if (!m_Display)
	{
		throw GameException(EXCEP_ALLEG_DISPLAY_FAILED);
	}

	m_Timer = al_create_timer(ALLEGRO_BPS_TO_SECS(m_TargetFramesPerSecond));
	if (!m_Timer)
	{
		throw GameException(EXCEP_ALLEG_TIMER_FAILED);
	}

	m_EventQueue = al_create_event_queue();
	if (!m_EventQueue)
	{
		throw GameException(EXCEP_ALLEG_EQUEUE_FAILED);
	}

	al_register_event_source(m_EventQueue, al_get_display_event_source(m_Display));
	al_register_event_source(m_EventQueue, al_get_timer_event_source(m_Timer));
}

void GameEngine::run()
{
	al_start_timer(m_Timer);
	
	m_GameActive = true;
	bool redrawScene = true;
	GameStateInterface* currentState = getCurrentState();

	while(m_GameActive)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(m_EventQueue, &event);

		switch(event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				m_GameActive = false;
				break;

			case ALLEGRO_EVENT_TIMER:
				redrawScene = true;
				break;

			default:
				log(std::string("Unhandled Event | type #") + std::to_string(event.type));
		}
		
		if (redrawScene && al_is_event_queue_empty(m_EventQueue))
		{
			m_FrameCount += 1;

			currentState->update(this);
			currentState->draw(this);

			al_flip_display();

			redrawScene = false;
		}
	}

}

void GameEngine::pushState(GameStateInterface* state)
{
	if (!m_StateStack.empty())
	{
		m_StateStack.top()->pause();
	}
	
	m_StateStack.push(state);
}

void GameEngine::popState()
{
	if (m_StateStack.empty())
		throw GameException(EXCEP_STATE_UNEXPECTED_EMPTY);

	delete m_StateStack.top();
	m_StateStack.pop();

	if (!m_StateStack.empty())
	{
		m_StateStack.top()->resume();
	}
}

void GameEngine::changeState(GameStateInterface* state)
{
	if (m_StateStack.empty())
		throw GameException(EXCEP_STATE_UNEXPECTED_EMPTY);

	delete m_StateStack.top();
	m_StateStack.pop();
	
	m_StateStack.push(state);
}

GameStateInterface* GameEngine::getCurrentState()
{
	if (m_StateStack.empty())
		throw GameException(EXCEP_STATE_UNEXPECTED_EMPTY);
	
	return m_StateStack.top();
}

void GameEngine::log(std::string msg)
{
	std::cout << "debug log: " << msg << std::endl;
}

ALLEGRO_BITMAP* GameEngine::screen()
{
	return al_get_backbuffer(m_Display);
}
