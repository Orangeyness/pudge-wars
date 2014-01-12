#ifndef H_OBSERVER_
#define H_OBSERVER_

#include "Event.h"

#include <forward_list>

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
		virtual void notify(const Event& event) { }
};


#endif
