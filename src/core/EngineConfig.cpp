#include "core/EngineConfig.h"
#include "core/GameException.h"

#include <cstdlib>

EngineConfig::EngineConfig()
{
	m_Config = NULL;
	
	m_ResolutionWidth = CONFIG_DEFAULT_RESOLUTION_WIDTH;
	m_ResolutionHeight = CONFIG_DEFAULT_RESOLUTION_HEIGHT;
	m_Fullscreen = CONFIG_DEFAULT_FULLSCREEN;
	m_FrameSpeed = CONFIG_DEFAULT_FRAME_SPEED;
}

void EngineConfig::load(std::string filename)
{
	if (m_Config != NULL)
	{
		al_destroy_config(m_Config);
	}

	m_Config = al_load_config_file(filename.c_str());

	if (m_Config == NULL)
	{
		THROW_GAME_EXCEPTION(EXCEP_CONFIG_FILE_MISSING);
	}

	loadResolutionWidth();
	loadResolutionHeight();
	loadFullscreen();
	loadFrameSpeed();
}

EngineConfig::~EngineConfig()
{
	if (m_Config != NULL)
	{
		al_destroy_config(m_Config);
	}
}

void EngineConfig::saveResolutionWidth()
{
	al_set_config_value(m_Config, "Display", "ResolutionWidth", std::to_string(m_ResolutionWidth).c_str());
}

void EngineConfig::saveResolutionHeight()
{
	al_set_config_value(m_Config, "Display", "ResolutionHeight", std::to_string(m_ResolutionHeight).c_str());
}

void EngineConfig::saveFullscreen()
{
	al_set_config_value(m_Config, "Display", "Fullscreen", std::to_string((m_Fullscreen ? 1 : 0)).c_str());
}

void EngineConfig::saveFrameSpeed()
{
	al_set_config_value(m_Config, "Game", "FrameSpeed", std::to_string(m_FrameSpeed).c_str());
}

void EngineConfig::loadResolutionWidth()
{
	const char* val = al_get_config_value(m_Config, "Display", "ResolutionWidth");

	if (val == NULL) return;

	m_ResolutionWidth = strtol(val, NULL, 10);
}

void EngineConfig::loadResolutionHeight()
{
	const char* val = al_get_config_value(m_Config, "Display", "ResolutionHeight");

	if (val == NULL) return;

	m_ResolutionHeight = strtol(val, NULL, 10);
}

void EngineConfig::loadFullscreen()
{
	const char* val = al_get_config_value(m_Config, "Display", "Fullscreen");

	if (val == NULL) return;

	m_Fullscreen = (strtol(val, NULL, 10) == 1);
}

void EngineConfig::loadFrameSpeed()
{
	const char* val = al_get_config_value(m_Config, "Game", "FrameSpeed");

	if (val == NULL) return;

	m_FrameSpeed = strtol(val, NULL, 10);
}

int EngineConfig::getResolutionWidth() const { return m_ResolutionWidth; }
int EngineConfig::getResolutionHeight() const { return m_ResolutionHeight; }
bool EngineConfig::getFullscreen() const { return m_Fullscreen; }
int EngineConfig::getFrameSpeed() const { return m_FrameSpeed; }

void EngineConfig::setResolutionWidth(int width) { m_ResolutionWidth = width; }
void EngineConfig::setResolutionHeight(int height) { m_ResolutionHeight = height; }
void EngineConfig::setFullscreen(bool fullscreen) { m_Fullscreen = fullscreen; }
void EngineConfig::setFrameSpeed(int frameSpeed) { m_FrameSpeed = frameSpeed; }



void EngineConfig::save(std::string filename)
{
	if (m_Config == NULL)
	{
		m_Config = al_create_config();
	}

	saveResolutionWidth();
	saveResolutionHeight();
	saveFullscreen();
	saveFrameSpeed();	

	al_save_config_file(filename.c_str(), m_Config);
}
