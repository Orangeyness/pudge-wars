#include "core/events/BufferedEventService.h"
#include "core/GameConstants.h"
#include "core/GameException.h"
#include "core/GameDebugWindow.h"

BufferedEventService::BufferedEventService() { }

BufferedEventService::~BufferedEventService() { }

void BufferedEventService::addListener(EventObserver* listener)
{
	m_Listeners.emplace_front(listener, EVENT_TYPE_ALL);
}

void BufferedEventService::addListener(EventObserver* listener, EventType typeMask)
{
	m_Listeners.emplace_front(listener, typeMask);
}

void BufferedEventService::removeListener(EventObserver* listener)
{
	m_Listeners.remove_if(
		[&listener](const std::pair<EventObserver*, EventType>& obj) { return (obj.first == listener); }
		);
}

void BufferedEventService::broadcast(const Event& event)
{
	m_BroadcastEvents.push_front(event);
}

void BufferedEventService::directMessage(EventObserver* recipant, const Event& event)
{
	m_DirectEvents.emplace_front(recipant, event);
}

inline void cleanupEventArgs(const Event& event)
{
	EventArgs* args = event.getArgs();
	if (args != NULL) delete args;
}

void BufferedEventService::doRoute()
{
	#ifdef DEBUG
	int directMessageCount = 0;
	int broadcastMessageCount = 0;
	#endif

	auto directIter = m_DirectEvents.begin();
	while (directIter != m_DirectEvents.end())
	{
		EventObserver* recipant = (*directIter).first;
		Event event = (*directIter).second;

		recipant->notify(event);

		cleanupEventArgs(event);
		directIter = m_DirectEvents.erase(directIter);
		
		#ifdef DEBUG
		directMessageCount ++;
		#endif
	}
	
	auto broadcastIter = m_BroadcastEvents.begin();
	while (broadcastIter != m_BroadcastEvents.end())
	{
		Event event = *broadcastIter;

		for (auto& EventObserverMaskPair : m_Listeners)
		{
			/* std::cout << int_to_hex_string(EventObserverMaskPair.second) << " | "
					  << int_to_hex_string(event.getType()) << " | "
					  << int_to_hex_string(EventObserverMaskPair.second & event.getType())
					  << std::endl; */
	
			if ((EventObserverMaskPair.second & event.getType()) == event.getType()) 
			{
				EventObserverMaskPair.first->notify(event);
			}
		}

		cleanupEventArgs(event);
		broadcastIter = m_BroadcastEvents.erase(broadcastIter);

		#ifdef DEBUG
		broadcastMessageCount ++;
		#endif
	}

	DEBUG_SHOW("DEBUG MAIN", "direct events", std::to_string(directMessageCount));
	DEBUG_SHOW("DEBUG MAIN", "broadcast events", std::to_string(broadcastMessageCount));
	DEBUG_SHOW("DEBUG MAIN", "total events", std::to_string(directMessageCount + broadcastMessageCount));
}
