#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

void Triangle::setTriangle(F4 aPos, F4 bPos, F4 cPos, F4 pCol)
{
	this->a.pos = aPos;
	this->b.pos = bPos;
	this->c.pos = cPos;
	this->a.col = pCol;
	this->b.col = pCol;
	this->c.col = pCol;
}

void Triangle::move(F2 shift)
{
	this->a.pos.x += shift.x;
	this->b.pos.x += shift.x;
	this->c.pos.x += shift.x;
	this->a.pos.y += shift.y;
	this->b.pos.y += shift.y;
	this->c.pos.y += shift.y;
}

void Triangle::rotateAtA(float angle)
{
	float zeroAngle = atan2f(b.pos.y - a.pos.y, b.pos.x - a.pos.x) + angle;
	float sideLength = sqrtf(((b.pos.x - a.pos.x) * (b.pos.x - a.pos.x)) + ((b.pos.y - a.pos.y) * (b.pos.y - a.pos.y)));
	b.pos.x = (cosf(zeroAngle) * sideLength) + a.pos.x;
	b.pos.y = (sinf(zeroAngle) * sideLength) + a.pos.y;
	zeroAngle = atan2f(c.pos.y - a.pos.y, c.pos.x - a.pos.x) + angle;
	sideLength = sqrtf(((c.pos.x - a.pos.x) * (c.pos.x - a.pos.x)) + ((c.pos.y - a.pos.y) * (c.pos.y - a.pos.y)));
	c.pos.x = (cosf(zeroAngle) * sideLength) + a.pos.x;
	c.pos.y = (sinf(zeroAngle) * sideLength) + a.pos.y;
}

_POINT Triangle::getA()
{
	return this->a;
}

_POINT Triangle::getB()
{
	return this->b;
}

_POINT Triangle::getC()
{
	return this->c;
}
