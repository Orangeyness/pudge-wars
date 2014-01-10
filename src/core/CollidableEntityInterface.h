#ifndef H_COLLIDABLE_ENTITY_INTERFACE_
#define H_COLLIDABLE_ENTITY_INTERFACE_

#include "GameEntityInterface.h"
#include "GeometryHelper.h"
#include "Observer.h"

class CollidableEntityInterface : public GameEntityInterface, public virtual Observer
{
	protected:
		double m_Radius;
		Vector2D m_Position;

	public:
		CollidableEntityInterface() : GameEntityInterface() {}
		virtual void draw() = 0;

		virtual bool isCollidingWith(CollidableEntityInterface* other);
		
		virtual Vector2D getPosition();
		virtual double getRadius();
};


#endif
