#ifndef H_ENTITY_BOUNDING_BOX_
#define H_ENTITY_BOUNDING_BOX_

#include "core/entities/EntityCollidable.h"

class EntityBoundingBox : public virtual EntityCollidable
{
	protected:
		Vector2D m_BoundingBoxOrigin;
		double m_BoundingBoxWidth;
		double m_BoundingBoxHeight;

		void updateBoundingBoxSize(double width, double height);
		void updateBoundingBoxOrigin(const Vector2D& origin);

	public:
		virtual Rect getBoundingBox();
		virtual CollidableType getType();
};


#endif
