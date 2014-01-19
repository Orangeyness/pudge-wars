#ifndef H_EVENT_OBSERVER_
#define H_EVENT_OBSERVER_

#include "core/events/Event.h"

class EventObserver 
{
	private:
		bool m_Deaf = false;

	protected:
		void startIgnoringEvents();
		void startReceivingEvents();

	public:
		virtual ~EventObserver() {}
		bool isDeaf();
		virtual void notify(const Event& event);
		virtual void processEvent(const Event& event) { } 
};


#endif
