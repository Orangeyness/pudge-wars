#ifndef H_SERVICE_LOCATOR_
#define H_SERVICE_LOCATOR_

#include "core/services/EventService.h"

class ServiceLocator
{
	public:
		static void AddService(EventService* service);
		static void RemoveService(EventService* service);

		static EventService* GetEventService();

};

#endif
