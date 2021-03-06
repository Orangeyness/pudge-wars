#include "pudge-wars/HookableInterface.h"

#include "core/GameException.h"
#include "core/GameConstants.h"
#include "core/services/ServiceLocator.h"
#include "core/events/Event.h"

HookableInterface::HookableInterface()
	: m_HookEventObserver(*this)
{
	m_HookEntityId = ENTITY_ID_NULL;
}

void HookableInterface::attachHook(int hookId, const Vector2D& position)
{
	m_HookEntityId = hookId;
}

void HookableInterface::dettachHook()
{
	m_HookEntityId = ENTITY_ID_NULL;
}

bool HookableInterface::isAttachedToHook()
{
	return m_HookEntityId != ENTITY_ID_NULL;
}

void HookableInterface::attachSecondHookBehaviour(int currentHook, int newHook, const Vector2D& position)
{
	attachHook(newHook, position);
}

HookableInterface::HookEventObserver::HookEventObserver(HookableInterface& parent)
	: m_Parent(parent) 
{
	ServiceLocator::GetEventService()->addListener(this, EVENT_TYPE_ENTITY);
}

HookableInterface::HookEventObserver::~HookEventObserver()
{
	ServiceLocator::GetEventService()->removeListener(this);
}

void HookableInterface::HookEventObserver::processEvent(const Event& event)
{
	// All entity events should have EntityEventArg type or a descent
	EntityEventArgs* args = event.getArgs<EntityEventArgs*>();
	
	switch(event.getType())
	{
		case EVENT_TYPE_HOOK_ATTACH:
		{
			/*
				Check if the attach event is calling us out by id.
				If so attach it if not already attached to a hook otherwise
				call attachSecondHookBehaviour to determine what happens.
			*/
			if (m_Parent.id() != args->getEntityId()) break;

			DoubleEntityPositionEventArgs* dArgs = event.getArgs<DoubleEntityPositionEventArgs*>();

			int newHookId = dArgs->getSecondEntityId();
			Vector2D newPosition = dArgs->getPosition();
			if (m_Parent.m_HookEntityId == newHookId) break;

			if (m_Parent.isAttachedToHook())
			{
				m_Parent.attachSecondHookBehaviour(m_Parent.m_HookEntityId, newHookId, newPosition);
			}
			else
			{
				m_Parent.attachHook(newHookId, newPosition);
			}

			break;
		}

		case EVENT_TYPE_HOOK_DETACH:
		{
			/* 
				Tells us we're now detached from the hook.
			*/
			if (m_Parent.m_HookEntityId == args->getEntityId())
			{
				m_Parent.dettachHook();
			}
			
			break;
		}

		case EVENT_TYPE_ENTITY_MOVE:
		{
			/*
				Check if it is the hook that moved, if so moveToHook
			*/
			if (m_Parent.m_HookEntityId == args->getEntityId())
			{
				EntityPositionEventArgs* args = event.getArgs<EntityPositionEventArgs*>();
	
				m_Parent.moveToHook(args->getPosition());
			}
	
			break;
		}
		
	}
}
