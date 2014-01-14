#ifndef H_MESSAGE_ROUTER
#define H_MESSAGE_ROUTER

#include "Observer.h"
#include "GameEntityInterface.h"

#include <vector>
#include <list>			//TODO: optimize with custom forward_list
#include <forward_list>
#include <utility>

class MessageRouter
{
	protected:
		std::list<Event> m_BroadcastEvents;
		std::list<std::pair<Observer*, Event>> m_DirectEvents;
		std::forward_list<std::pair<Observer*, EventType>> m_Listeners;

	public:
		MessageRouter();
		~MessageRouter();

		void registerListener(Observer* listener);
		void registerListener(Observer* listener, EventType typeMask);
		void deregisterListener(Observer* listener);

		void broadcast(const Event& event);
		void directMessage(Observer* recipant, const Event& event);
	
		void doRoute();
		
		static MessageRouter* Instance();
};


#endif
