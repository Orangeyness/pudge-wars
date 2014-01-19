#ifndef H_SERVICE_LOCATOR_
#define H_SERVICE_LOCATOR_

#include "core/services/EventService.h"
#include "core/services/GameDataService.h"


class ServiceLocator
{
	public:
		static void AddService(EventService* service);
		static void AddService(GameDataService* service);
		static void RemoveService(EventService* service);
		static void RemoveService(GameDataService* service);

		static EventService* GetEventService();
		static GameDataService* GetGameDataService();

};

#endif
