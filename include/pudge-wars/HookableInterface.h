#ifndef H_HOOKABLE_INTERFACE
#define H_HOOKABLE_INTERFACE

#include "core/helpers/GeometryHelper.h"
#include "core/events/Event.h"
#include "core/events/EventObserver.h"
#include "core/entities/Entity.h"

class HookableInterface : public virtual Entity
{
	private:
		int m_HookEntityId;	

		class HookEventObserver : public EventObserver
		{
			private:
				HookableInterface& m_Parent;

			public:
				HookEventObserver(HookableInterface& parent);
				~HookEventObserver();
				virtual void processEvent(const Event& event);
		};

		HookEventObserver m_HookEventObserver;

	protected:
		virtual void attachHook(int hookId, const Vector2D& position);
		virtual void dettachHook();
		virtual void moveToHook(const Vector2D& hookPosition) = 0;
		virtual void attachSecondHookBehaviour(int currentHook, int newHook, const Vector2D& position);
		virtual bool isAttachedToHook();

	public:
		HookableInterface();
		virtual ~HookableInterface() { }

};

#endif
