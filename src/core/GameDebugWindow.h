#ifndef _GAME_DEBUG_WINDOW_
#define _GAME_DEBUG_WINDOW_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <unordered_map>
#include <map>
#include <string>

class GameDebugWindow
{
	private:
		std::unordered_map<std::string, std::string> m_TitleToMessageMap;
		std::multimap<int, std::string> m_PriorityToTitleMap;
		std::string m_WindowName;

		ALLEGRO_DISPLAY* m_Display;
		ALLEGRO_FONT*	 m_Font;

	public: 
		GameDebugWindow(std::string name, int width, int height);
		~GameDebugWindow();

		void addDetail(std::string title, std::string message);
		void addDetail(std::string title, std::string message, int priority);
		void removeDetail(std::string title);
	
		void refresh();
	
		static GameDebugWindow* GetByName(std::string name);
		static void RefreshAll();
};

#ifdef DEBUG
	#define DEBUG_WINDOW(windowname,w,h) GameDebugWindow gdw(windowname,w,h)
	#define DEBUG_SHOW(windowname, ...) GameDebugWindow::GetByName(windowname)->addDetail(__VA_ARGS__)
	#define DEBUG_REFRESH(windowname) GameDebugWindow::GetByName(windowname)->refresh()
	#define DEBUG_REFRESH_ALL() GameDebugWindow::RefreshAll()
#else
	#define DEBUG_WINDOW(windowname,w,h)  
	#define DEBUG_SHOW(windowname, ...)  
	#define DEBUG_REFRESH(windowname)  
	#define DEBUG_REFRESH_ALL()  
#endif

#endif
