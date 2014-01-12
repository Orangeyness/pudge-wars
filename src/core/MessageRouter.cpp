#include "MessageRouter.h"
#include "GameConstants.h"
#include "GameException.h"

static MessageRouter* _instance = NULL;

MessageRouter* MessageRouter::Instance()
{
	return _instance;
}

MessageRouter::MessageRouter()
{
	if (_instance != NULL)
		throw GameException(EXCEP_MULTIPLE_MESSAGE_ROUTERS);

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

inline void notifyObserver(Observer* obs, const Event& event)
{
	if (!obs->isDeaf()) obs->notify(event);
}

inline void cleanupEventArgs(const Event& event)
{
	EventArgs* args = event.getArgs();
	if (args != NULL) delete args;
}

void MessageRouter::doRoute()
{
	auto directIter = m_DirectEvents.cbegin();
	auto directIterOrigBegin = m_DirectEvents.cbefore_begin();

	auto broadcastIter = m_BroadcastEvents.cbegin();
	auto broadcastIterOrigBegin = m_BroadcastEvents.cbefore_begin();

	while (directIter != m_DirectEvents.cend())
	{
		Observer* recipant = (*directIter).first;
		Event event = (*directIter).second;

		notifyObserver(recipant, event);

		cleanupEventArgs(event);
		directIter ++;
	}
	
	m_DirectEvents.erase_after(directIterOrigBegin, m_DirectEvents.cend());

	while (broadcastIter != m_BroadcastEvents.cend())
	{
		Event event = *broadcastIter;

		for (auto& ObserverMaskPair : m_Listeners)
		{
			if (ObserverMaskPair.second & event.getType()) 
			{
				notifyObserver(ObserverMaskPair.first, event);
			}
		}

		cleanupEventArgs(event);
		broadcastIter ++;
	}

	m_BroadcastEvents.erase_after(broadcastIterOrigBegin, m_BroadcastEvents.cend());
}
