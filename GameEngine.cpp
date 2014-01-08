#include "GameEngine.h"
#include "GameException.h"

GameEngine::GameEngine()
{
	// Settings
	m_TargetFramesPerSecond = 70;
	
	// State
	m_FrameCount = 0;
	m_FrameCountThisSecond = 0;
	m_LastFrameRate = 0;
	m_LastSecondTime = 0;

	m_GameActive = false;

	// Allegro Engine
	m_Display = NULL;
	m_EventQueue = NULL;
	m_RedrawTimer = NULL;
}

GameEngine::~GameEngine()
{
	// Cleanup allegro engine objects
	if (m_RedrawTimer) al_destroy_timer(m_RedrawTimer);
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

	if (!al_install_keyboard())
	{
		throw GameException(EXCEP_ALLEG_KEYBOARD_FAILED);
	}

	if (!al_install_mouse())
	{
		throw GameException(EXCEP_ALLEG_MOUSE_FAILED);
	}

	//Temporary Display Options
	al_set_new_display_flags(ALLEGRO_OPENGL);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_RENDER_METHOD, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_CAN_DRAW_INTO_BITMAP, 1, ALLEGRO_SUGGEST);

	al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR | ALLEGRO_VIDEO_BITMAP);

	m_Display = al_create_display(640, 480);
	if (!m_Display)
	{
		throw GameException(EXCEP_ALLEG_DISPLAY_FAILED);
	}

	m_RedrawTimer = al_create_timer(ALLEGRO_BPS_TO_SECS(m_TargetFramesPerSecond));
	if (!m_RedrawTimer)
	{
		throw GameException(EXCEP_ALLEG_TIMER_FAILED);
	}

	m_EventQueue = al_create_event_queue();
	if (!m_EventQueue)
	{
		throw GameException(EXCEP_ALLEG_EQUEUE_FAILED);
	}

	al_register_event_source(m_EventQueue, al_get_display_event_source(m_Display));
	al_register_event_source(m_EventQueue, al_get_timer_event_source(m_RedrawTimer));
	al_register_event_source(m_EventQueue, al_get_keyboard_event_source());
}

void GameEngine::run()
{
	al_start_timer(m_RedrawTimer);
	
	m_GameActive = true;
	m_LastSecondTime = al_current_time();
	bool redrawScene = true;

	while(m_GameActive)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(m_EventQueue, &event);

		switch(event.type)
		{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				m_GameActive = false;
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
					m_GameActive = false;
				break;

			case ALLEGRO_EVENT_TIMER:
				redrawScene = true;
				break;
		}
		
		if (redrawScene && al_is_event_queue_empty(m_EventQueue))
		{
			GameStateInterface* currentState = getCurrentState();
			currentState->update(this);
			currentState->draw(this);

			al_flip_display();

			calculateFrameRate();

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

void GameEngine::quit()
{
	m_GameActive = false;
}

GameStateInterface* GameEngine::getCurrentState()
{
	if (m_StateStack.empty())
		throw GameException(EXCEP_STATE_UNEXPECTED_EMPTY);
	
	return m_StateStack.top();
}

void GameEngine::log(std::string msg)
{
	std::cout << std::endl << "debug log: " << msg << std::endl;
}

ALLEGRO_BITMAP* GameEngine::screen()
{
	return al_get_backbuffer(m_Display);
}

void GameEngine::calculateFrameRate()
{
	m_FrameCount += 1;
	m_FrameCountThisSecond += 1;

	double currentTime = al_current_time();
	if (currentTime - m_LastSecondTime >= 1.0)
	{
		m_LastFrameRate = m_FrameCountThisSecond / (currentTime - m_LastSecondTime);
		m_LastSecondTime = currentTime;
		m_FrameCountThisSecond = 0;

		std::cout 	<< "\rFrame Rate: " << m_LastFrameRate 
					<< " (Total: " << m_FrameCount << ")" << std::flush;
	}
}
