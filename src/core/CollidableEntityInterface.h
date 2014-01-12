#ifndef H_COLLIDABLE_ENTITY_INTERFACE_
#define H_COLLIDABLE_ENTITY_INTERFACE_

#include "GameEntityInterface.h"
#include "GeometryHelper.h"
#include "Observer.h"
#include "GameDebugWindow.h"

typedef int CollidableType;

class CollidableEntityInterface : public GameEntityInterface, public virtual Observer
{
	protected:
		Vector2D m_Position;
		bool m_Solid;
	
	public:
		CollidableEntityInterface();
		virtual CollidableType getType() = 0;
		virtual bool isSolid();
		virtual Vector2D getPosition();
};


#endif
