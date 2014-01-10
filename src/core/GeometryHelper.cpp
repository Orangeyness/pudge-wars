#include "GeometryHelper.h"

/* returns euclidean distance between two points */
double point_distance(double x1, double y1, double x2, double y2)
{
	double dx, dy;
	dx = x1 - x2;
	dy = y1 - y2;
		
	return (double)sqrt((dx * dx) + (dy * dy));
}

/* returns arctan betwen two points */
double point_direction(double x1, double y1, double x2, double y2)
{
	double dx, dy;
	dx = x1 - x2;
	dy = y1 - y2;

	return atan2(-dy, dx);
}

/* returns x component of vector calculated using a length and direction */
double lengthdir_x(double len, double dir)
{
	return cos( dir ) * len;
}

/* returns y component of vector calculated using a length and direction */
double lengthdir_y(double len, double dir)
{
	return -sin( dir ) * len;
}


Vector2D::Vector2D()
{
	set(0, 0);
}

Vector2D::Vector2D(double _x, double _y)
{
	set(_x, _y);
}

void Vector2D::set(double _x, double _y)
{
	x = _x;
	y = _y;
}

double Vector2D::toDirection()
{
	return std::atan2(-y, x);
}


static Vector2D fromDirection(double direction)
{
	return Vector2D( lengthdir_x(1, direction) , lengthdir_y(1, direction) );
}

double Vector2D::magnitude()
{
	return sqrt(x*x + y*y);
}

void Vector2D::normalise()
{
	double m = magnitude();
	
	if (m == 0) return;

	x /= m;
	y /= m;
}

double Vector2D::euclideanDist(const Vector2D& other)
{
	double xDiff = x - other.x;
	double yDiff = y - other.y;
	
	return sqrt((xDiff * xDiff) + (yDiff * yDiff));
}

double Vector2D::sqauredEuclideanDist(const Vector2D& other)
{
	double xDiff = x - other.x;
	double yDiff = y - other.y;
	
	return (xDiff * xDiff) + (yDiff * yDiff);
}

double Vector2D::directionToPoint(double otherX, double otherY)
{
	return point_direction(otherX, otherY, x, y);
}

double Vector2D::directionToPoint(const Vector2D& other)
{
	return point_direction(other.x, other.y, x, y);
}
