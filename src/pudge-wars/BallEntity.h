#ifndef H_BALL_ENTITY_
#define H_BALL_ENTITY_

#include "../core/RadialEntityInterface.h"
#include "../core/GeometryHelper.h"

class BallEntity : public RadialEntityInterface
{
	public:
		BallEntity(Vector2D position, double radius);
		
		virtual void draw();

};

#endif
