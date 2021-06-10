#pragma once
#include "PointList.h"

class TriangleList
{
public:
	TriangleList();
	~TriangleList();

	void setDX(ID3D11Device* device, ID3D11DeviceContext* context);

	void setTriangleCount(unsigned count);
	Triangle* getTriangle(unsigned index);

	void update();
	void draw();

private:
	Triangle* triangleList;
	unsigned* indexes;
	unsigned countOfTriangle;

	ID3D11Buffer* triangleBuff;
	ID3D11Buffer* indexBuff;
	ID3D11DeviceContext* context;
	ID3D11Device* device;
};

