#ifndef H_OBSERVER_
#define H_OBSERVER_

#include "Event.h"

class Observer 
{
	private:
		bool m_Deaf = false;

	protected:
		void startIgnoringEvents();
		void startReceivingEvents();

	public:
		virtual ~Observer() {}
		bool isDeaf();
		virtual void notify(const Event& event);
		virtual void processEvent(const Event& event) { }
};


#endif
