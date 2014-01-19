#include "core/services/ServiceLocator.h"
#include "core/GameException.h"
#include "core/GameConstants.h"

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
}
