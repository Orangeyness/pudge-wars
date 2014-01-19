#ifndef H_COLLISION_HELPER_
#define H_COLLISION_HELPER_

#include "core/entities/EntityCollidable.h"
#include "core/entities/EntityRadial.h"
#include "core/entities/EntityBoundingBox.h"
#include "core/helpers/GeometryHelper.h"

class CollisionHelper
{
	public:
		static bool isColliding(EntityCollidable* first, EntityCollidable* second);
		static bool isColliding(EntityRadial* first, EntityRadial* second);
		static bool isColliding(EntityBoundingBox* first, EntityRadial* second);
		static bool isColliding(EntityBoundingBox* first, EntityBoundingBox* second);

		static double calculateReflectAngle(EntityCollidable* surface, Vector2D position, double direction);
		static double calculateReflectAngle(EntityRadial* surface, Vector2D position, double direction);
		static double calculateReflectAngle(EntityBoundingBox* surface, Vector2D position, double direction);

		static double calculateReflectAngle(double surfaceTangent, double direction);
};


#endif
