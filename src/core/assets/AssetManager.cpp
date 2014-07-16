#include "core/assets/AssetManager.h"
#include "core/GameConstants.h"
#include "core/GameException.h"

AssetManager::AssetManager() { }

AssetManager::AssetManager(std::string baseDirectory)
	: m_BaseDirectory(baseDirectory) { }

AssetManager::~AssetManager()
{
	if (!m_Bitmaps.empty()) clearBitmaps();
}

inline void AssetManager::_loadBitmap(std::string name)
{
	if (m_Bitmaps.find(name) == m_Bitmaps.end())
	{
		m_Bitmaps[name] = al_load_bitmap((m_BaseDirectory + name).c_str());

		if (m_Bitmaps[name] == NULL) THROW_GAME_EXCEPTION(EXCEP_BITMAP_FILE_MISSING);
	}
}

void AssetManager::preloadBitmap(std::string name)
{
	_loadBitmap(name);
}

ALLEGRO_BITMAP* AssetManager::loadBitmap(std::string name)
{	
	_loadBitmap(name);

	return m_Bitmaps[name];
}

void AssetManager::clearBitmaps()
{
	for (auto& x : m_Bitmaps)
	{
		al_destroy_bitmap(x.second);
	}

	m_Bitmaps.erase(m_Bitmaps.begin(), m_Bitmaps.end());
}
