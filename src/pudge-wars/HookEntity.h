#ifndef H_HOOK_ENTITY
#define H_HOOK_ENTITY

#include "../core/GeometryHelper.h"
#include "../core/RadialEntityInterface.h"
#include <list>

class HookEntity : public RadialEntityInterface
{
	protected:
		int m_ParentId;
		double m_Direction;
		double m_Speed;
		int m_LifeRemaining;
		std::list<Vector2D> m_TailList;

	public:
		HookEntity(int parentId, Vector2D position, double direction, double speed, int life);
		~HookEntity();
	
		virtual EntityStatus update();
		virtual void draw();
		virtual void processEvent(const Event& event);
};


#endif
