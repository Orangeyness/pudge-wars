#include "core/services/ServiceLocator.h"
#include "core/GameException.h"
#include "core/GameConstants.h"

/*
	This is so hacky and I love it.
*/

#define SERVICE_ADD(ServiceType)									\
		static ServiceType * _registered##ServiceType = NULL;		\
																	\
		void ServiceLocator::AddService(ServiceType * service)		\
		{															\
			if (_registered##ServiceType != NULL)					\
				THROW_GAME_EXCEPTION(EXCEP_SERVICE_EXISTS);			\
																	\
			_registered##ServiceType = service;						\
		}															\
		void ServiceLocator::RemoveService(ServiceType * service)	\
		{															\
			if (_registered##ServiceType == NULL) 					\
				THROW_GAME_EXCEPTION(EXCEP_SERVICE_NONEXISTANT);	\
																	\
			if (_registered##ServiceType != service) 				\
				THROW_GAME_EXCEPTION(EXCEP_SERVICE_NOT_IN_USE);		\
																	\
			_registered##ServiceType = NULL;						\
		}															\
		ServiceType * ServiceLocator::Get##ServiceType()			\
		{															\
			if (_registered##ServiceType == NULL) 					\
				THROW_GAME_EXCEPTION(EXCEP_SERVICE_NONEXISTANT);	\
																	\
			return _registered##ServiceType;						\
		}															\
		ServiceType * ServiceLocator::TryGet##ServiceType()			\
		{															\
			return _registered##ServiceType;						\
		}
		
SERVICE_ADD(EventService);
SERVICE_ADD(GameDataService);

		
/*
static EventService* _registeredEventService = NULL;

void ServiceLocator::AddService(EventService* service)
{
	if (_registeredEventService != NULL) 
		THROW_GAME_EXCEPTION(EXCEP_SERVICE_EXISTS);

	_registeredEventService = service;
}

void ServiceLocator::RemoveService(EventService* service)
{
	if (_registeredEventService == NULL) 
		THROW_GAME_EXCEPTION(EXCEP_SERVICE_NONEXISTANT);

	if (_registeredEventService != service) 
		THROW_GAME_EXCEPTION(EXCEP_SERVICE_NOT_IN_USE);

	_registeredEventService = NULL;
}

EventService* ServiceLocator::GetEventService()
{
	if (_registeredEventService == NULL) 
		THROW_GAME_EXCEPTION(EXCEP_SERVICE_NONEXISTANT);

	return _registeredEventService;
}*/
