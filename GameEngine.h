#ifndef _GAME_ENGINE_
#define _GAME_ENGINE_

#include "GameStateInterface.h"

#include <allegro5/allegro.h>

#include <iostream>
#include <stack>

class GameEngine
{
	private:
		// Settings
		int m_TargetFramesPerSecond;

		// State
		long m_FrameCount;
		bool m_GameActive;
		std::stack<GameStateInterface*> m_StateStack;

		// Allegro controls
		ALLEGRO_DISPLAY* 		m_Display;
		ALLEGRO_EVENT_QUEUE* 	m_EventQueue;
		ALLEGRO_TIMER* 			m_Timer;		

		// Helpers
		GameStateInterface* getCurrentState();

	public: 
		GameEngine();
		~GameEngine();

		void initialise();
		void run();

		void pushState(GameStateInterface* state);
		void popState();
		void changeState(GameStateInterface* state);

		void log(std::string msg);

		ALLEGRO_BITMAP* screen();
};


#endif
