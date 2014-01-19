#ifndef H_BUFFERED_EVENT_SERVICE_
#define H_BUFFERED_EVENT_SERVICE_

#include "core/services/EventService.h"
#include "core/events/EventObserver.h"
#include "core/entities/Entity.h"

#include <vector>
#include <list>			//TODO: optimize with custom forward_list
#include <forward_list>
#include <utility>

class BufferedEventService : public EventService
{
	protected:
		std::list<Event> m_BroadcastEvents;
		std::list<std::pair<EventObserver*, Event>> m_DirectEvents;
		std::forward_list<std::pair<EventObserver*, EventType>> m_Listeners;

	public:
		BufferedEventService();
		~BufferedEventService();

		virtual void addListener(EventObserver* listener);
		virtual void addListener(EventObserver* listener, EventType typeMask);
		virtual void removeListener(EventObserver* listener);
		virtual void broadcast(const Event& event);
		virtual void directMessage(EventObserver* recipant, const Event& event);
	
		void doRoute();
};

#endif
