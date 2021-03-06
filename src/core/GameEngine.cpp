#include "core/GameEngine.h"
#include "core/GameException.h"
#include "core/GameDebugWindow.h"
#include "core/services/ServiceLocator.h"

GameEngine::GameEngine(EngineConfig* config)
	: m_DataService(*this)
{
	m_Config = config;
	
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

	//Register Services
	ServiceLocator::AddService(&m_DataService);
}

GameEngine::~GameEngine()
{
	// Cleanup allegro engine objects
	if (m_RedrawTimer) al_destroy_timer(m_RedrawTimer);
	if (m_Display) al_destroy_display(m_Display);
	if (m_EventQueue) al_destroy_event_queue(m_EventQueue);

	// Cleanup State stack
	while(!m_StateStack.empty())
	{
		delete m_StateStack.top();
		m_StateStack.pop();
	}

	ServiceLocator::RemoveService(&m_DataService);
}

void GameEngine::initialise()
{
	if (!al_init())
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_ENGINE_FAILED);
	}	

	if (!al_init_font_addon())
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_FONT_FAILED);
	}

	if (!al_init_image_addon())
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_IMAGE_FAILED);
	}

	if (!al_install_keyboard())
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_KEYBOARD_FAILED);
	}

	if (!al_install_mouse())
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_MOUSE_FAILED);
	}

	//Temporary Display Options
	al_set_new_display_flags(ALLEGRO_OPENGL);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_RENDER_METHOD, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_CAN_DRAW_INTO_BITMAP, 1, ALLEGRO_SUGGEST);

	int originalDisplayFlags = al_get_new_display_flags();
	int displayFlags = 0;
	if (m_Config->getFullscreen())
	{
		displayFlags = displayFlags | ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_NOFRAME;
	}

	al_set_new_display_flags(displayFlags);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR | ALLEGRO_VIDEO_BITMAP);

	if (m_Config->getResolutionWidth() < 0 || m_Config->getResolutionHeight() < 0)
	{
		ALLEGRO_DISPLAY_MODE largest_display_mode;
		al_get_display_mode(al_get_num_display_modes() - 1, &largest_display_mode);

		m_Config->setResolutionWidth(largest_display_mode.width);
		m_Config->setResolutionHeight(largest_display_mode.height);

		//std::cout << m_Config->getResolutionWidth() << " " << m_Config->getResolutionHeight() << endl;
	}

	m_Display = al_create_display(m_Config->getResolutionWidth(), m_Config->getResolutionHeight());
	if (!m_Display)
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_DISPLAY_FAILED);
	}
	al_set_new_display_flags(originalDisplayFlags);

	m_RedrawTimer = al_create_timer(ALLEGRO_BPS_TO_SECS(m_Config->getFrameSpeed()));
	if (!m_RedrawTimer)
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_TIMER_FAILED);
	}

	m_EventQueue = al_create_event_queue();
	if (!m_EventQueue)
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_EQUEUE_FAILED);
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

	DEBUG_WINDOW("DEBUG MAIN", 300, 180);

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

			DEBUG_REFRESH_ALL();
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
		THROW_GAME_EXCEPTION(EXCEP_STATE_UNEXPECTED_EMPTY);

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
		THROW_GAME_EXCEPTION(EXCEP_STATE_UNEXPECTED_EMPTY);

	delete m_StateStack.top();
	m_StateStack.pop();
	
	m_StateStack.push(state);
}

void GameEngine::quit()
{
	m_GameActive = false;
}

ALLEGRO_BITMAP* GameEngine::screen()
{
	return al_get_backbuffer(m_Display);
}

GameEngine::DataService::DataService(GameEngine& parent)
	: m_Parent(parent) { }

int GameEngine::DataService::getScreenWidth()
{
	return al_get_display_width(m_Parent.m_Display);
}

int GameEngine::DataService::getScreenHeight()
{
	return al_get_display_height(m_Parent.m_Display);
}

uint64_t GameEngine::DataService::getGameFrameCount()
{
	return m_Parent.m_FrameCount;
}

// Helper Methods
GameStateInterface* GameEngine::getCurrentState()
{
	if (m_StateStack.empty())
		THROW_GAME_EXCEPTION(EXCEP_STATE_UNEXPECTED_EMPTY);
	
	return m_StateStack.top();
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

		DEBUG_SHOW("DEBUG MAIN", "Frame Rate", std::to_string(m_LastFrameRate));
		DEBUG_SHOW("DEBUG MAIN", "Frame Total", std::to_string(m_FrameCount));
	}
}
