#ifndef H_HOOK_ENTITY
#define H_HOOK_ENTITY

#include "../core/GeometryHelper.h"
#include "../core/RadialEntityInterface.h"

class HookEntity : public RadialEntityInterface
{
	protected:
		double m_Direction;
		double m_Speed;
		int m_LifeRemaining;

	public:
		HookEntity(Vector2D position, double direction, double speed, int life);

		virtual EntityStatus update();
		virtual void draw();
};


#endif
