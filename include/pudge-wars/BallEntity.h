#ifndef H_BALL_ENTITY_
#define H_BALL_ENTITY_

#include "core/entities/EntityRadial.h"
#include "core/helpers/GeometryHelper.h"
#include "pudge-wars/HookableInterface.h"

class BallEntity : public EntityRadial,  public HookableInterface
{
	protected:
		Vector2D m_HookPosition;
		Vector2D m_PositionPrevious;

	public:
		BallEntity(Vector2D position, double radius);
		
		virtual void draw(Rect viewWindow);
		virtual void moveToHook(const Vector2D& hookPosition);
		virtual void attachHook(int hookId, const Vector2D& hookPosition);
		virtual void dettachHook();
		virtual void processEvent(const Event& event);

};

#endif
