#include "Qube.h"



Qube::Qube()
{
	this->points = nullptr;
	this->triangles = nullptr;
	this->device = nullptr;
	this->context = nullptr;
}


Qube::~Qube()
{
	delete this->points;
	delete this->triangles;
	this->device = nullptr;
	this->context = nullptr;
}

void Qube::create(F2 pos, F2 size, ID3D11Device* device, ID3D11DeviceContext* context)
{
	Triangle *trg;
	F4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
	F4 b0f4, b1f4, b2f4;
	this->device = device;
	this->context = context;
	this->triangles = new TriangleList();
	this->points = new PointList();
	(this->triangles)->setDX(this->device, this->context);
	(this->triangles)->setTriangleCount(4);
	(this->points)->setDX(this->device, this->context);
	(this->points)->setCount(1);

	((this->points)->getPoint(0u))->set(pos.x, pos.y);

	//trg 0 - right
	trg = (this->triangles)->getTriangle(0u);

	b0f4 = { pos.x, pos.y, 0.0f, 1.0f };
	b1f4 = { pos.x + (size.x / 2.0f),pos.y + (size.y / 2.0f),0.0f,1.0f };
	b2f4 = { pos.x + (size.x / 2.0f),pos.y - (size.y / 2.0f),0.0f,1.0f };

	trg->setTriangle(b0f4, b1f4, b2f4, color);

	// trg 1 - down
	trg = (this->triangles)->getTriangle(1u);

	b1f4.y -= size.y;
	b2f4.x -= size.x;

	trg->setTriangle(b0f4, b1f4, b2f4, color);

	// trg 2 - left
	trg = (this->triangles)->getTriangle(2u);

	b1f4.x -= size.x;
	b2f4.y += size.y;

	trg->setTriangle(b0f4, b1f4, b2f4, color);

	// trg 3 - left
	trg = (this->triangles)->getTriangle(3u);

	b1f4.y += size.y;
	b2f4.x += size.x;

	trg->setTriangle(b0f4, b1f4, b2f4, color);

}

void Qube::move(F2 shift)
{
	((this->points)->getPoint(0u))->mov(shift.x, shift.y);

	for (unsigned t = 0; t < 4; t++) {
		((this->triangles)->getTriangle(t))->move(shift);
	}
}

void Qube::setPos(F2 pos)
{
	F2 shift = { pos.x - ((this->triangles)->getTriangle(0u))->getA().pos.x , pos.y - ((this->triangles)->getTriangle(0u))->getA().pos.y };
	((this->points)->getPoint(0u))->set(pos.x, pos.y);
	for (unsigned t = 0; t < 4; t++) {
		((this->triangles)->getTriangle(t))->move(shift);
	}
}

void Qube::rotate(float angle)
{
	for (unsigned t = 0; t < 4; t++) {
		((this->triangles)->getTriangle(t))->rotateAtA(angle);
	}
}

void Qube::draw()
{
	(this->triangles)->update();
	(this->triangles)->draw();
	(this->points)->update();
	(this->points)->draw();
}

F2 Qube::getPos()
{
	return ((this->points)->getPoint(0u))->get2DPos();
}
