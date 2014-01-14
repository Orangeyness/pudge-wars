#include "MessageRouter.h"
#include "GameConstants.h"
#include "GameException.h"
#include "GameDebugWindow.h"

#include <iostream>

static MessageRouter* _instance = NULL;

MessageRouter* MessageRouter::Instance()
{
	if (_instance == NULL)
		THROW_GAME_EXCEPTION(EXCEP_MISSING_MESSAGE_ROUTER);

	return _instance;
}

MessageRouter::MessageRouter()
{
	if (_instance != NULL)
		THROW_GAME_EXCEPTION(EXCEP_MULTIPLE_MESSAGE_ROUTERS);

	_instance = this;
}

MessageRouter::~MessageRouter()
{
	_instance = NULL;
}

void MessageRouter::registerListener(Observer* listener)
{
	m_Listeners.emplace_front(listener, EVENT_TYPE_ALL);
}

void MessageRouter::registerListener(Observer* listener, EventType typeMask)
{
	m_Listeners.emplace_front(listener, typeMask);
}

void MessageRouter::deregisterListener(Observer* listener)
{
	m_Listeners.remove_if(
		[&listener](const std::pair<Observer*, EventType>& obj) { return (obj.first == listener); }
		);
}

void MessageRouter::broadcast(const Event& event)
{
	m_BroadcastEvents.push_front(event);
}

void MessageRouter::directMessage(Observer* recipant, const Event& event)
{
	m_DirectEvents.emplace_front(recipant, event);
}

inline void cleanupEventArgs(const Event& event)
{
	EventArgs* args = event.getArgs();
	if (args != NULL) delete args;
}

void MessageRouter::doRoute()
{
	#ifdef DEBUG
	int directMessageCount = 0;
	int broadcastMessageCount = 0;
	#endif

	auto directIter = m_DirectEvents.begin();
	while (directIter != m_DirectEvents.end())
	{
		Observer* recipant = (*directIter).first;
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

		for (auto& ObserverMaskPair : m_Listeners)
		{
			/* std::cout << int_to_hex_string(ObserverMaskPair.second) << " | "
					  << int_to_hex_string(event.getType()) << " | "
					  << int_to_hex_string(ObserverMaskPair.second & event.getType())
					  << std::endl; */
	
			if ((ObserverMaskPair.second & event.getType()) == event.getType()) 
			{
				ObserverMaskPair.first->notify(event);
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