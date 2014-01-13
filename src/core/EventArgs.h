#ifndef H_EVENT_ARGS_
#define H_EVENT_ARGS_

#include "GameEntityInterface.h"
#include "GeometryHelper.h"

class EventArgs
{
	public:
		virtual	~EventArgs() { }	
};

class EntityEventArgs : public EventArgs
{
	protected:
		int m_EntityId;

	public:
		EntityEventArgs(GameEntityInterface* entity);
		GameEntityInterface* getEntity() const;
		int getEntityId() const;
};

class EntityPositionEventArgs : public EntityEventArgs
{
	protected:
		Vector2D m_Position;

	public:
		EntityPositionEventArgs(GameEntityInterface* entity, const Vector2D& pos);
		Vector2D getPosition() const;
};

#endif
