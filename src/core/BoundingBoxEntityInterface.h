#ifndef H_BOUNDING_BOX_ENTITY_INTERFACE
#define H_BOUNDING_BOX_ENTITY_INTERFACE

#include "CollidableEntityInterface.h"

class BoundingBoxEntityInterface : public CollidableEntityInterface
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
