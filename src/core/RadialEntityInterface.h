#ifndef H_RADIAL_ENTITY_INTERFACE
#define H_RADIAL_ENTITY_INTERFACE

#include "CollidableEntityInterface.h"

class RadialEntityInterface : public CollidableEntityInterface
{
	protected:
		double m_Radius;

	public:
		virtual double getRadius();
		virtual CollidableType getType();
};


#endif
