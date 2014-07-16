#include "pudge-wars/ViewPort.h"

#include "core/services/ServiceLocator.h"
#include "core/services/GameDataService.h"
#include "core/services/EventService.h"

ViewPort::ViewPort() { }

ViewPort::ViewPort(Entity* followEntity, const Vector2D& initalPosition, const Vector2D& mapSize)
{

	init(followEntity, initalPosition, mapSize);
}

ViewPort::~ViewPort()
{
	EventService* es = ServiceLocator::TryGetEventService();
	if (es != NULL) es->removeListener(this);
}

void ViewPort::init(Entity* followEntity, const Vector2D& initalPosition, const Vector2D& mapSize)
{
	m_EntityFollowId = followEntity->id();
	m_MapSize = mapSize;

	GameDataService* gameData = ServiceLocator::GetGameDataService();
	m_View.width = gameData->getScreenWidth();
	m_View.height = gameData->getScreenHeight();

	reposition(initalPosition);

	ServiceLocator::GetEventService()->addListener(this, EVENT_TYPE_ENTITY_MOVE);
}

Rect ViewPort::get()
{
	return m_View;
}

Vector2D ViewPort::position()
{
	return m_View.position();
}

void ViewPort::processEvent(const Event& event)
{
	EntityPositionEventArgs* args = event.getArgs<EntityPositionEventArgs*>();
	
	if (args->getEntityId() == m_EntityFollowId)
	{
		reposition(args->getPosition());
	}
}

void ViewPort::reposition(const Vector2D& position)
{
	Vector2D newPosition = position - (m_View.size() / 2);
	
	newPosition.x = std::max(0.0, std::min(m_MapSize.x, newPosition.x));
	newPosition.y = std::max(0.0, std::min(m_MapSize.y, newPosition.y));

	m_View.position(newPosition);
}
