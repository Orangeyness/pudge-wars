#ifndef H_GEOMETRY_HELPER_
#define H_GEOMETRY_HELPER_

#include <cmath>

/*	Note Geometry is done with the assumption that +y 
	is pointing down.

		-				+x
			+----------> 
			| This
			| Quadrant 
			| is the 
		+y	| screen
			v

	Directions and angles are passed in radians. Degrees only 
	used to display debugging.
*/

#define DEG_TO_RAD(x) (x * (M_PI / 180))
#define RAD_TO_DEG(x) (x * (180 / M_PI))

// Base Helper Functions
double point_distance(double x1, double y1, double x2, double y2);
double point_direction(double x1, double y1, double x2, double y2);
double lengthdir_x(double len, double dir);
double lengthdir_y(double len, double dir);

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

		double directionToPoint(double otherX, double otherY);
		double directionToPoint(const Vector2D& other);
		Vector2D manhattanDist(const Vector2D& other);
		double euclideanDist(const Vector2D& other);
		double sqauredEuclideanDist(const Vector2D& other);

		static Vector2D fromDirection(double direction);
};

class Rect
{
	public:
		double x, y, width, height;

		Rect();
		Rect(double _x, double _y, double _width, double _height);
		Rect(const Vector2D& point1, const Vector2D& point2);
				
		void resize(double width, double height);
		void position(const Vector2D& point);
		void position(const Vector2D& point, double offsetX, double offsetY);
		void position(const Vector2D& point, const Vector2D& offset);

		Vector2D center() const;
		double area() const;

		double top() const;
		double bot() const;
		double left() const;
		double right() const;

		bool contains(double x, double y);
		bool contains(const Vector2D& point);
		bool intersects(const Rect& r);
		bool intersects(const Vector2D& circleCenter, double radius);


};

#endif
