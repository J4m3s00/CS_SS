#pragma once

typedef enum BUFFER_TYPE
{
	BUFFER_TYPE_VERTEX_BUFFER,
	BUFFER_TYPE_INDEX_BUFFER
};

class DXBuffer
{
public:
	DXBuffer(BUFFER_TYPE type, const void* data, UINT elementSize, UINT count);
	~DXBuffer();

	void Bind();
private:
	ID3D11Buffer* fpBuffer;
	UINT fCount;
	UINT fElementSize;
};