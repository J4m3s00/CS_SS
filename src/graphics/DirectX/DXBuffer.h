#pragma once

typedef enum BUFFER_TYPE
{
	BUFFER_TYPE_VERTEX_BUFFER,
	BUFFER_TYPE_INDEX_BUFFER,
	BUFFER_TYPE_CONSTANT_BUFFER
};

class DXBuffer
{
public:
	DXBuffer(BUFFER_TYPE type, const void* data, UINT elementSize, UINT count);
	~DXBuffer();

	void UpdateData(const void* data, UINT elementSize, UINT count);

	void Bind();

	UINT GetCount() const { return fCount; }
private:
	BUFFER_TYPE fType;
	ID3D11Buffer* fpBuffer;
	UINT fCount;
	UINT fElementSize;
};