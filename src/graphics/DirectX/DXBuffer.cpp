#include <prefix.h>

DXBuffer::DXBuffer(BUFFER_TYPE type, const void* data, UINT elementSize, UINT count)
	: fElementSize(elementSize), fCount(count)
{
	D3D11_BUFFER_DESC bd = {};
	UINT bindFlags = 0;
	switch (type)
	{
	case BUFFER_TYPE_VERTEX_BUFFER:
		bindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;
	case BUFFER_TYPE_INDEX_BUFFER:
		bindFlags = D3D11_BIND_INDEX_BUFFER;
		break;
	};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = fElementSize * fCount;
	bd.BindFlags = bindFlags;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA ms;
	ms.pSysMem = data;
	DXContext::sInstance.GetDevice()->CreateBuffer(&bd, &ms, &fpBuffer);
}

DXBuffer::~DXBuffer()
{
	fpBuffer->Release();
}

void DXBuffer::Bind()
{
	UINT offset = 0;
	DXContext::sInstance.GetDeviceContext()->IASetVertexBuffers(0, 1, &fpBuffer, &fElementSize, &offset);
}