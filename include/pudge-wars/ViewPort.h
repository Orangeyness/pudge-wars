#ifndef H_VIEW_PORT_
#define H_VIEW_PORT_

#include "core/events/EventObserver.h"
#include "core/entities/Entity.h"
#include "core/helpers/GeometryHelper.h"

class ViewPort : public EventObserver
{
	public:
		ViewPort();
		ViewPort(Entity* followEntity, const Vector2D& intialPosition, const Vector2D& mapSize);
		~ViewPort();

		void init(Entity* followEntity, const Vector2D& intialPosition, const Vector2D& mapSize);
		void clean();

		Rect get();
		void processEvent(const Event& event);

	private:
		Rect m_View;
		Vector2D m_MapSize;
		int m_EntityFollowId;

		void reposition(const Vector2D& reposition);
};


#endif
