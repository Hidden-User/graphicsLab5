#pragma once
#include "Triangle.h"

class PointList
{
public:
	PointList();
	~PointList();

	void setDX(ID3D11Device* device, ID3D11DeviceContext* context);

	void setCount(unsigned count);
	Point* getPoint(unsigned pos);
	unsigned size();

	void update();
	void draw();

private:
	Point* points;
	unsigned *indexes;
	unsigned count;

	ID3D11Buffer* pointBuff;
	ID3D11Buffer* indexBuff;
	ID3D11DeviceContext* context;
	ID3D11Device* device;

};

