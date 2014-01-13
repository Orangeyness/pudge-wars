#include "GameDebugWindow.h"
#include "GameConstants.h"
#include "GameException.h"

static std::unordered_map<std::string, GameDebugWindow*> _NameToWindowMap;

GameDebugWindow::GameDebugWindow(std::string name, int width, int height)
{
	ALLEGRO_BITMAP* prevTargetBitmap = al_get_target_bitmap();
	
	if (_NameToWindowMap[name] != NULL)
		THROW_GAME_EXCEPTION(EXCEP_DEBUG_WINDOW_EXISTS);

	_NameToWindowMap[name] = this;
	m_WindowName = name;

	m_Display = al_create_display(width, height);
	m_Font = al_create_builtin_font();
	
	if (!m_Display)
	{
		THROW_GAME_EXCEPTION(EXCEP_ALLEG_DISPLAY_FAILED);
	}
	
	al_set_window_title(m_Display, m_WindowName.c_str()); 
	al_set_target_bitmap(prevTargetBitmap);
} 
GameDebugWindow::~GameDebugWindow()
{
	_NameToWindowMap.erase(m_WindowName);

	al_destroy_display(m_Display);
	al_destroy_font(m_Font);
}

void GameDebugWindow::addDetail(std::string title, std::string message)
{
	addDetail(title, message, 0);
}

void GameDebugWindow::addDetail(std::string title, std::string message, int priority)
{
	if (m_TitleToMessageMap.count(title) == 0)
	{
		m_PriorityToTitleMap.insert(std::pair<int, std::string>(priority, title));
	}
	
	m_TitleToMessageMap[title] = message;
}

void GameDebugWindow::removeDetail(std::string title)
{
	m_TitleToMessageMap.erase(title);

	//Don't bother removing the priority atm
	//as this is just debug shit
}

void GameDebugWindow::refresh()
{
	ALLEGRO_BITMAP* prevTargetBitmap = al_get_target_bitmap();
	al_set_target_bitmap(al_get_backbuffer(m_Display));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	int drawOffset = 20;
	int messageOffset = 150;
	int lineCount = 0;
	int lineHeight = 16;

	auto it = m_PriorityToTitleMap.cbegin();
	while (it != m_PriorityToTitleMap.cend())
	{
		std::string title = (*it).second;
		
		if (m_TitleToMessageMap.count(title) == 1)
		{
			std::string message = m_TitleToMessageMap[title];

			al_draw_text(	m_Font, al_map_rgb(75, 150, 75), 
							drawOffset, drawOffset + lineCount * lineHeight, 
							0, title.c_str());

			al_draw_text(	m_Font, al_map_rgb(75, 150, 75), 
							drawOffset + messageOffset, drawOffset + lineCount * lineHeight, 
							0, message.c_str());

			lineCount ++;
		}	

		it ++;
	}

	al_flip_display();

	al_set_target_bitmap(prevTargetBitmap);
}

GameDebugWindow* GameDebugWindow::GetByName(std::string name)
{
	if (_NameToWindowMap[name] == NULL)
		THROW_GAME_EXCEPTION(EXCEP_DEBUG_WINDOW_MISSING);

	return _NameToWindowMap[name];
}

void GameDebugWindow::RefreshAll()
{
	auto it = _NameToWindowMap.cbegin();
	while (it != _NameToWindowMap.cend())
	{
		(*it).second->refresh();

		it ++;
	}
}
