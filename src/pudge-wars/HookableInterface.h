#ifndef H_HOOKABLE_INTERFACE
#define H_HOOKABLE_INTERFACE

#include "../core/GeometryHelper.h"
#include "../core/Event.h"
#include "../core/Observer.h"
#include "../core/GameEntityInterface.h"

class HookableInterface : public virtual GameEntityInterface
{
	private:
		int m_HookEntityId;	

		class HookObserver : public Observer
		{
			private:
				HookableInterface& m_Parent;

			public:
				HookObserver(HookableInterface& parent);
				~HookObserver();
				virtual void processEvent(const Event& event);
		};

		HookObserver m_Observer;

	protected:
		virtual void attachHook(int hookId);
		virtual void dettachHook();
		virtual void moveToHook(const Vector2D& hookPosition) = 0;
		virtual void attachSecondHookBehaviour(int currentHook, int newHook);
		virtual bool isAttachedToHook();

	public:
		HookableInterface();
		virtual ~HookableInterface() { }

};

#endif
