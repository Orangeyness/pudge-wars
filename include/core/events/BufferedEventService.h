#ifndef H_BUFFERED_EVENT_SERVICE_
#define H_BUFFERED_EVENT_SERVICE_

#include "core/events/EventObserver.h"
#include "core/entities/Entity.h"

#include <vector>
#include <list>			//TODO: optimize with custom forward_list
#include <forward_list>
#include <utility>

class BufferedEventService
{
	protected:
		std::list<Event> m_BroadcastEvents;
		std::list<std::pair<EventObserver*, Event>> m_DirectEvents;
		std::forward_list<std::pair<EventObserver*, EventType>> m_Listeners;

	public:
		BufferedEventService();
		~BufferedEventService();

		void registerListener(EventObserver* listener);
		void registerListener(EventObserver* listener, EventType typeMask);
		void deregisterListener(EventObserver* listener);

		void broadcast(const Event& event);
		void directMessage(EventObserver* recipant, const Event& event);
	
		void doRoute();
		
		static BufferedEventService* Instance();
};


#endif
