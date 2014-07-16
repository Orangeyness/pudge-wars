#ifndef H_ASSET_MANAGER_
#define H_ASSET_MANAGER_

#include "core/services/AssetService.h"

#include <unordered_map>

class AssetManager : public AssetService
{
	private:	
		std::string m_BaseDirectory;
		std::unordered_map<std::string, ALLEGRO_BITMAP*> m_Bitmaps;

		inline void _loadBitmap(std::string name);

	public:	
		AssetManager();
		AssetManager(std::string baseDirectory);
		~AssetManager();

		virtual void preloadBitmap(std::string name);
		virtual ALLEGRO_BITMAP* loadBitmap(std::string name);

		void clearBitmaps();
	
};


#endif
