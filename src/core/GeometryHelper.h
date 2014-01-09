#ifndef _GEOMETRY_HELPER_
#define _GEOMETRY_HELPER_

class Vector2D 
{
	public:
		double x, y;
		Vector2D();
		Vector2D(double _x, double _y);
		void set(double _x, double _y);
		double toDirection();
		double magnitude();
		void normalise();

		static Vector2D fromDirection(double direction);
};

#endif
