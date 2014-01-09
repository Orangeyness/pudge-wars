#include "GeometryHelper.h"

#include "gtest/gtest.h"

#include <math.h>

TEST(GeometryHelper, Vector2DDefaultConstructor) 
{
	Vector2D v;

	ASSERT_EQ(v.x, 0);
	ASSERT_EQ(v.y, 0);
}

TEST(GeometryHelper, Vector2DCoordConstructor)
{
	Vector2D v (5, 9);

	ASSERT_EQ(v.x, 5);
	ASSERT_EQ(v.y, 9);
}

TEST(GeometryHelper, Vector2DSet)
{
	Vector2D v;

	ASSERT_EQ(v.x, 0);
	ASSERT_EQ(v.y, 0);

	v.set(5, 9);

	ASSERT_EQ(v.x, 5);
	ASSERT_EQ(v.y, 9);

	v.set(9.6, 5.1);

	ASSERT_EQ(v.x, 9.6);
	ASSERT_EQ(v.y, 5.1);
}

TEST(GeometryHelper, Vector2DMagnitude)
{
	Vector2D v;
	
	ASSERT_EQ(0, v.magnitude());

	v.set(3, 4);

	ASSERT_EQ(5, v.magnitude());

	v.set(3.464101615, 2);

	ASSERT_NEAR(4.0, v.magnitude(), 0.000000001);
}

TEST(GeometryHelper, Vector2DtoDirection)
{
	Vector2D v;
	
	ASSERT_EQ(v.toDirection(), 0);

	v.set(0, 1);

	ASSERT_EQ(v.toDirection(), M_PI/2);

	v.set(1, 0);

	ASSERT_EQ(v.toDirection(), 0);

	v.set(0, -1);

	ASSERT_EQ(v.toDirection(), -M_PI/2);

	v.set(-1, 0);

	ASSERT_EQ(v.toDirection(), M_PI);

	v.set(3, 3);	
	ASSERT_EQ(v.toDirection(), M_PI/4);
}

TEST(GeometryHelper, Vector2Dnormalise)
{
	Vector2D v;
	v.normalise();
	ASSERT_EQ(v.x, 0);
	ASSERT_EQ(v.y, 0);

	v.set(0, 1);
	v.normalise();
	ASSERT_EQ(v.x, 0);
	ASSERT_EQ(v.y, 1);

	v.set(0, 2);
	v.normalise();
	ASSERT_EQ(v.x, 0);
	ASSERT_EQ(v.y, 1);

	v.set(2, 2);
	v.normalise();
	ASSERT_DOUBLE_EQ(v.x, 1.0/(double)sqrt(2));
	ASSERT_DOUBLE_EQ(v.y, 1.0/(double)sqrt(2));

	v.set(2, 0);
	v.normalise();
	ASSERT_EQ(v.x, 1);
	ASSERT_EQ(v.y, 0);

	v.set(-7, 9);
	v.normalise();
	ASSERT_DOUBLE_EQ(v.x, -7.0/(double)sqrt(130));
	ASSERT_DOUBLE_EQ(v.y, 9.0/(double)sqrt(130));

}

/*
TEST(GeometryHelper, Vector2DfromDirection)
{
	Vector2D v = Vector2D::fromDirection(M_PI);

	ASSERT_EQ(-1, v.x);
	ASSERT_EQ(0, v.y);
}*/
