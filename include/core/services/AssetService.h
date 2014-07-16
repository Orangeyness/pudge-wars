#ifndef H_ASSET_SERVICE_
#define H_ASSET_SERVICE_

#include <allegro5/allegro.h>
#include <string>

class AssetService
{
	public:
		virtual void preloadBitmap(std::string name) = 0;
		virtual ALLEGRO_BITMAP* loadBitmap(std::string name) = 0;
};


#endif
