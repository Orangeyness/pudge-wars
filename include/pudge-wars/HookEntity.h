#ifndef H_HOOK_ENTITY
#define H_HOOK_ENTITY

#include "core/helpers/GeometryHelper.h"
#include "core/entities/EntityRadial.h"
#include <list>

class HookEntity : public EntityRadial
{
	protected:
		int m_ParentId;
		double m_Direction;
		double m_Speed;
		double m_DistanceMax;
		double m_DistanceCurrent;
		Vector2D m_CasterPosition;
		double m_CasterRadius;
		std::list<Vector2D> m_TailList;
		bool m_Retracting;
		bool m_HookAttached;

		void updateForwardHook();
		EntityStatus updateRetractingHook();

	public:
		HookEntity(int parentId, Vector2D position, double direction, double radius, double speed, double maxDistance);
		~HookEntity();
	
		virtual EntityStatus update();
		virtual void draw(Rect viewWindow);
		virtual void processEvent(const Event& event);
};


#endif
