#ifndef H_GAME_DATA_SERVICE_
#define H_GAME_DATA_SERVICE_

#include "core/GameConstants.h"

class GameDataService
{
	public:
		virtual int getScreenWidth() = 0;
		virtual int getScreenHeight() = 0;
		virtual uint64_t getGameFrameCount() = 0;
		virtual ~GameDataService() { }
};


#endif
