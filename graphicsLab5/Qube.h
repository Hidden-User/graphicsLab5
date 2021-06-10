#pragma once
#include "TriangleList.h"


class Qube
{
public:
	Qube();
	~Qube();

	void create(F2 pos, F2 size, ID3D11Device* device, ID3D11DeviceContext* context);
	void move(F2 shift);
	void setPos(F2 pos);
	void rotate(float angle);

	void draw();

	F2 getPos();

private:
	TriangleList *triangles;
	PointList *points;

	ID3D11Device* device;
	ID3D11DeviceContext* context;

};

