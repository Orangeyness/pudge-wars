#ifndef H_ENTITY_RADIAL_
#define H_ENTITY_RADIAL_

#include "core/entities/EntityCollidable.h"

class EntityRadial : public virtual EntityCollidable
{
	protected:
		double m_Radius;

	public:
		virtual double getRadius();
		virtual CollidableType getType();
};


#endif
