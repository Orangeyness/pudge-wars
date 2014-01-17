#ifndef H_EVENT_ARGS_
#define H_EVENT_ARGS_

#include "GameEntityInterface.h"
#include "GeometryHelper.h"

class EventArgs
{
	public:
		virtual	~EventArgs() { }	
};

class EntityEventArgs : public virtual EventArgs
{
	protected:
		int m_EntityId;

	public:
		EntityEventArgs(GameEntityInterface* entity);
		GameEntityInterface* getEntity() const;
		int getEntityId() const;

		template<typename T> 
		T getEntity() const
		{
			return getEntity()->toType<T>();
		}

		template<typename T> 
		T tryGetEntity() const
		{
			return getEntity()->tryToType<T>();
		}
};

class DoubleEntityEventArgs : public virtual EntityEventArgs
{
	protected:
		int m_SecondEntityId;
	
	public:
		DoubleEntityEventArgs(GameEntityInterface* entity, GameEntityInterface* secondEntity);
		GameEntityInterface* getSecondEntity() const;
		int getSecondEntityId() const;

		template<typename T> 
		T getSecondEntity() const
		{
			return getSecondEntity()->toType<T>();
		}

		template<typename T> 
		T tryGetSecondEntity() const
		{
			return getSecondEntity()->tryToType<T>();
		}
		
};

class PositionEventArgs : public virtual EventArgs
{
	protected:
		Vector2D m_Position;

	public:
		PositionEventArgs(const Vector2D& pos);
		const Vector2D& getPosition() const;
};

class EntityPositionEventArgs : public virtual EntityEventArgs, public virtual PositionEventArgs
{
	public:
		EntityPositionEventArgs(GameEntityInterface* entity, const Vector2D& pos);
};

class DoubleEntityPositionEventArgs : public virtual DoubleEntityEventArgs, public virtual PositionEventArgs
{

	public:
		DoubleEntityPositionEventArgs(	GameEntityInterface* entity, 
										GameEntityInterface* secondEntity,
						 				const Vector2D& pos);
};

#endif
