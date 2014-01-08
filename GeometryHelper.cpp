#include "GeometryHelper.h"
#include <cmath>

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
	return std::atan2(y, x);
}

static Vector2D fromDirection(double direction)
{
	Vector2D v (1, tan(direction));

	v.normalise();

	return v;
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
