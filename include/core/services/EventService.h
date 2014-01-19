#ifndef H_EVENT_SERVICE_
#define H_EVENT_SERVICE_

#include "core/events/EventObserver.h"
#include "core/entities/Entity.h"

class EventService
{
	public:
		virtual void addListener(EventObserver* listener) = 0;
		virtual void addListener(EventObserver* listener, EventType typeMask) = 0;
		virtual void removeListener(EventObserver* listener) = 0;

		virtual void broadcast(const Event& event) = 0;
		virtual void directMessage(EventObserver* recipant, const Event& event) = 0;
		virtual ~EventService() { }
};

#endif
