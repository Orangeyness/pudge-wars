#include "HookableInterface.h"

#include "../core/GameException.h"
#include "../core/GameConstants.h"
#include "../core/MessageRouter.h"
#include "../core/Event.h"

HookableInterface::HookableInterface()
	: m_Observer(*this)
{
	m_HookEntityId = ENTITY_ID_NULL;
}

void HookableInterface::attachHook(int hookId)
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

void HookableInterface::attachSecondHookBehaviour(int currentHook, int newHook)
{
	attachHook(newHook);
}

HookableInterface::HookObserver::HookObserver(HookableInterface& parent)
	: m_Parent(parent) 
{
	MessageRouter::Instance()->registerListener(this, EVENT_TYPE_ENTITY);
}

HookableInterface::HookObserver::~HookObserver()
{
	MessageRouter::Instance()->deregisterListener(this);
}

void HookableInterface::HookObserver::processEvent(const Event& event)
{

	EntityEventArgs* args = dynamic_cast<EntityEventArgs*>(event.getArgs());
	if (args == NULL) THROW_GAME_EXCEPTION(EXCEP_EVENT_WRONG_ARGTYPE);
	
	switch(event.getType())
	{
		case EVENT_TYPE_HOOK_ATTACH:
		{
			if (m_Parent.id() != args->getEntityId()) break;

			DoubleEntityEventArgs* dArgs = dynamic_cast<DoubleEntityEventArgs*>(event.getArgs());
			if (dArgs == NULL) THROW_GAME_EXCEPTION(EXCEP_EVENT_WRONG_ARGTYPE);
			int newHookId = dArgs->getSecondEntityId();
			if (m_Parent.m_HookEntityId == newHookId) break;

			if (m_Parent.isAttachedToHook())
			{
				m_Parent.attachSecondHookBehaviour(m_Parent.m_HookEntityId, newHookId);
			}
			else
			{
				m_Parent.attachHook(newHookId);
			}

			break;
		}

		case EVENT_TYPE_HOOK_DETACH:
		{
			if (m_Parent.m_HookEntityId == args->getEntityId())
			{
				m_Parent.dettachHook();
			}
			
			break;
		}

		case EVENT_TYPE_ENTITY_MOVE:
		{
			if (m_Parent.m_HookEntityId == args->getEntityId())
			{
				EntityPositionEventArgs* args = dynamic_cast<EntityPositionEventArgs*>(event.getArgs());
				if (args == NULL) THROW_GAME_EXCEPTION(EXCEP_EVENT_WRONG_ARGTYPE);
	
				m_Parent.moveToHook(args->getPosition());
			}
	
			break;
		}
		
	}
}
