#ifndef H_GAME_ENGINE_
#define H_GAME_ENGINE_

#include "core/GameStateInterface.h"
#include "core/services/GameDataService.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <stack>

class GameEngine
{
	private:
		// Settings
		int m_TargetFramesPerSecond;

		// State
		uint64_t m_FrameCount;
		int m_FrameCountThisSecond;
		double m_LastFrameRate;
		double m_LastSecondTime;
		bool m_GameActive;
		std::stack<GameStateInterface*> m_StateStack;

		// StateAccessor
		class DataService : public GameDataService
		{
			private:
				GameEngine& m_Parent;
			public:
				DataService(GameEngine& parent);
				virtual int getScreenWidth();
				virtual int getScreenHeight();
				virtual uint64_t getGameFrameCount();
		} m_DataService;

		// Allegro controls
		ALLEGRO_DISPLAY* 		m_Display;
		ALLEGRO_EVENT_QUEUE* 	m_EventQueue;
		ALLEGRO_TIMER* 			m_RedrawTimer;		

		// Helper Methods
		GameStateInterface* getCurrentState();
		void calculateFrameRate();


	public: 
		GameEngine();
		~GameEngine();

		void initialise();
		void run();

		void pushState(GameStateInterface* state);
		void popState();
		void changeState(GameStateInterface* state);
		void quit();
	
		ALLEGRO_BITMAP* screen();
};


#endif
