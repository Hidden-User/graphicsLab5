#pragma once
#include "Point.h"

class Triangle
{
public:
	Triangle();
	~Triangle();

	void setTriangle(F4, F4, F4, F4 = { 0 });
	void move(F2 shift);
	void rotateAtA(float angle);
	//void rotateAtB(float angle);
	//void rotateAtC(float angle);
	_POINT getA();
	_POINT getB();
	_POINT getC();

private:
	_POINT a;
	_POINT b;
	_POINT c;

};

