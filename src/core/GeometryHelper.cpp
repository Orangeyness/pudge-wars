#include "GeometryHelper.h"

#include <algorithm>

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

Vector2D::Vector2D(double direction)
{
	set( lengthdir_x(1, direction) , lengthdir_y(1, direction) );
}

void Vector2D::set(double _x, double _y)
{
	x = _x;
	y = _y;
}

void Vector2D::moveInDirection(double len, double dir)
{
	x += lengthdir_x(len, dir);
	y += lengthdir_y(len, dir);
}

double Vector2D::toDirection()
{
	return std::atan2(-y, x);
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

Vector2D Vector2D::manhattanDist(const Vector2D& other)
{
	return Vector2D(std::abs(x - other.x), std::abs(y - other.y));
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


Vector2D Vector2D::operator +(const Vector2D& rhs) const
{
	return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator -(const Vector2D& rhs) const
{
	return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D& Vector2D::operator +=(const Vector2D& rhs)
{
	x += rhs.x;
	y += rhs.y;
	
	return *this;
}

Vector2D& Vector2D::operator -=(const Vector2D& rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

Rect::Rect()
{
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

Rect::Rect(const Vector2D& point1, const Vector2D& point2)
{
	x = std::min(point1.x, point2.x);
	y = std::min(point1.y, point2.y);
	double x2 = std::max(point1.x, point2.x);
	double y2 = std::max(point1.y, point2.y);

	width = x2 - x;
	height = y2 - y;
}

Rect::Rect(double _x, double _y, double _width, double _height)
{
	if (_width < 0)
	{
		x = _x - _width;
		width = -_width;
	}
	else
	{
		x = _x;
		width = _width;
	}

	if (_height < 0)
	{
		y = _y - _height;
		height = -_height;
	}
	else
	{
		y = _y;
		height = _height;
	}
}

void Rect::resize(double _width, double _height)
{
	width = _width;
	height = _height;
}

void Rect::position(const Vector2D& point)
{
	x = point.x;
	y = point.y;
}

void Rect::position(const Vector2D& point, double offsetX, double offsetY)
{
	x = point.x - offsetX;
	y = point.y - offsetY;
}

void Rect::position(const Vector2D& point, const Vector2D& offset)
{
	x = point.x - offset.x;
	y = point.y - offset.y;
}

double Rect::area() const
{
	return width * height;
}

double Rect::top() const
{
	return y + height;
}

double Rect::bot() const
{
	return y;
}

double Rect::left() const
{
	return x;
}

double Rect::right() const
{
	return x + width;
}

Vector2D Rect::center() const
{
	return Vector2D(x + width / 2, y + height / 2);
}

bool Rect::contains(double x, double y)
{
	return (x >= left() || x <= right()) && (y >= top() || y <= bot());
}

bool Rect::contains(const Vector2D& point)
{
	return contains(point.x, point.y);
}

bool Rect::intersects(const Rect& r)
{
	return (r.bot() >= top() && r.top() <= bot() && r.right() >= left() && r.left() <= right());
}

bool Rect::intersects(const Vector2D& circleCenter, double radius)
{
	// See:
	// http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection

	Vector2D rectCenter = center();
	
	Vector2D dist = rectCenter.manhattanDist(circleCenter);

	if (dist.x > width/2 + radius) return false;
	if (dist.y > height/2 + radius) return false;

	if (dist.x <= width/2) return true;
	if (dist.y <= height/2) return true;

	double cornerDiffX = dist.x - width/2;
	double cornerDiffY = dist.y - height/2;
	
	return ((cornerDiffX * cornerDiffX) + (cornerDiffY * cornerDiffY)) < (radius * radius);
}
