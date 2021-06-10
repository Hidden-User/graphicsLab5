#include "PointList.h"



PointList::PointList()
{
	this->indexes = nullptr;
	this->points = nullptr;
	this->pointBuff = nullptr;
	this->indexBuff = nullptr;
	this->context = nullptr;
	this->device = nullptr;
}


PointList::~PointList()
{
	if (this->indexes != nullptr) {
		delete[] this->indexes;
	}
	if (this->points != nullptr) {
		delete[] this->points;
	}
	if (this->pointBuff != nullptr) {
		(this->pointBuff)->Release();
	}
	if (this->indexBuff != nullptr) {
		(this->indexBuff)->Release();
	}
	this->context = nullptr;
	this->device = nullptr;
}

void PointList::setDX(ID3D11Device * device, ID3D11DeviceContext * context)
{
	this->device = device;
	this->context = context;
}

void PointList::setCount(unsigned count)
{
	HRESULT hr;
	F2 bf2 = { 0.0f, 0.0f };

	this->count = count;
	this->points = new Point[this->count];
	this->indexes = new unsigned[this->count];

	for (unsigned t = 0; t < this->count; t++) {
		this->indexes[t] = t;
		this->points[t] = bf2;
	}

	D3D11_SUBRESOURCE_DATA pointSR;
	pointSR.pSysMem = this->points;
	pointSR.SysMemPitch = 0;
	pointSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC* bd = new D3D11_BUFFER_DESC;
	bd->Usage = D3D11_USAGE_DYNAMIC;
	bd->ByteWidth = sizeof(Point) * this->count;
	bd->BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd->CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd->MiscFlags = 0;
	bd->StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(bd, &pointSR, &(this->pointBuff));

	if (FAILED(hr)) {
		MessageBox(NULL, "error create point buff", "err", MB_ICONSTOP | MB_OK);
	}

	D3D11_SUBRESOURCE_DATA indexSR;

	indexSR.pSysMem = &(this->indexes[0]);
	indexSR.SysMemPitch = 0;
	indexSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC* ibd = new D3D11_BUFFER_DESC;
	ibd->Usage = D3D11_USAGE_DEFAULT;
	ibd->ByteWidth = sizeof(unsigned) * this->count;
	ibd->BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd->CPUAccessFlags = 0;
	ibd->MiscFlags = 0;
	ibd->StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(ibd, &indexSR, &(this->indexBuff));

	if (FAILED(hr)) {
		MessageBox(NULL, "error create index buff", "err", MB_ICONSTOP | MB_OK);
	}
}

Point * PointList::getPoint(unsigned pos)
{
	if (pos >= this->count) {
		throw 0xFFFF;
	}
	return &(this->points[pos]);
}

unsigned PointList::size()
{
	return this->count;
}

void PointList::update()
{
	D3D11_MAPPED_SUBRESOURCE mpsr = { 0 };

	(this->context)->Map(this->pointBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mpsr);

	memcpy_s(mpsr.pData, this->count * sizeof(Point), this->points, this->count * sizeof(Point));

	(this->context)->Unmap(this->pointBuff, 0);

}

void PointList::draw() {
	UINT stride = sizeof(_POINT);
	UINT offset = 0;

	(this->context)->IASetVertexBuffers(0, 1, &(this->pointBuff), &stride, &offset);
	(this->context)->IASetIndexBuffer(this->indexBuff, DXGI_FORMAT_R32_UINT, 0);

	(this->context)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	(this->context)->DrawIndexed(this->count, 0, 0);
}

