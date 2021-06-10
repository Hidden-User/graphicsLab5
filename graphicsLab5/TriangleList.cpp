#include "TriangleList.h"



TriangleList::TriangleList()
{
	this->indexes = nullptr;
	this->triangleList = nullptr;
	this->triangleBuff = nullptr;
	this->indexBuff = nullptr;
	this->context = nullptr;
	this->device = nullptr;
}


TriangleList::~TriangleList()
{
	if (this->indexes != nullptr) {
		delete[] this->indexes;
	}
	if (this->triangleList != nullptr) {
		delete[] this->triangleList;
	}
	if (this->triangleBuff != nullptr) {
		(this->triangleBuff)->Release();
	}
	if (this->indexBuff != nullptr) {
		(this->indexBuff)->Release();
	}
	this->context = nullptr;
	this->device = nullptr;
}

void TriangleList::setDX(ID3D11Device * device, ID3D11DeviceContext * context)
{
	this->device = device;
	this->context = context;
}

void TriangleList::setTriangleCount(unsigned count)
{
	if (this->device == NULL || this->context == NULL) {
		return;
	}

	HRESULT hr = NULL;

	this->triangleList = new Triangle[count];
	this->indexes = new unsigned[count * 3];
	this->countOfTriangle = count;

	Triangle triangle = Triangle();

	for (unsigned t = 0; t < this->countOfTriangle; t++) {
		this->triangleList[t] = triangle;
		this->indexes[t * 3] = t * 3;
		this->indexes[(t * 3) + 1] = (t * 3) + 1;
		this->indexes[(t * 3) + 2] = (t * 3) + 2;
	}

	D3D11_SUBRESOURCE_DATA _triangleSR;

	_triangleSR.pSysMem = this->triangleList;
	_triangleSR.SysMemPitch = 0;
	_triangleSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC tbd;
	tbd.Usage = D3D11_USAGE_DYNAMIC;
	tbd.ByteWidth = sizeof(Triangle) * this->countOfTriangle;
	tbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tbd.MiscFlags = 0;
	tbd.StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(&tbd, &_triangleSR, &this->triangleBuff);

	if (FAILED(hr)) {
		MessageBox(NULL, "error create buff", "err", MB_ICONSTOP | MB_OK);
	}

	D3D11_SUBRESOURCE_DATA _IndexesSR;

	_IndexesSR.pSysMem = this->indexes;
	_IndexesSR.SysMemPitch = 0;
	_IndexesSR.SysMemSlicePitch = 0;

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(unsigned) * 3 * this->countOfTriangle;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	hr = (this->device)->CreateBuffer(&ibd, &_IndexesSR, &this->indexBuff);

	if (FAILED(hr)) {
		MessageBox(NULL, "error create buff", "err", MB_ICONSTOP | MB_OK);
	}
}

Triangle * TriangleList::getTriangle(unsigned index)
{
	return &(this->triangleList[index]);
}

void TriangleList::update()
{
	D3D11_MAPPED_SUBRESOURCE mpsr = { 0 };

	(this->context)->Map(this->triangleBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mpsr);

	memcpy(mpsr.pData, this->triangleList, sizeof(Triangle) * this->countOfTriangle);

	(this->context)->Unmap(this->triangleBuff, 0);

}

void TriangleList::draw()
{
	UINT stride = sizeof(_POINT);
	UINT offset = 0;

	(this->context)->IASetVertexBuffers(0, 1, &this->triangleBuff, &stride, &offset);
	(this->context)->IASetIndexBuffer(this->indexBuff, DXGI_FORMAT_R32_UINT, 0);

	(this->context)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	(this->context)->DrawIndexed(this->countOfTriangle * 3, 0, 0);

}
