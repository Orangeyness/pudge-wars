#ifndef H_ENTITY_COLLIDABLE_
#define H_ENTITY_COLLIDABLE_

#include "core/entities/Entity.h"
#include "core/helpers/GeometryHelper.h"
#include "core/events/EventObserver.h"
#include "core/GameDebugWindow.h"

typedef int CollidableType;

class EntityCollidable : public Entity, public virtual EventObserver
{
	protected:
		Vector2D m_Position;
		bool m_Solid;
	
	public:
		EntityCollidable();
		virtual CollidableType getType() = 0;
		virtual bool isSolid();
		virtual Vector2D getPosition();
};


#endif
