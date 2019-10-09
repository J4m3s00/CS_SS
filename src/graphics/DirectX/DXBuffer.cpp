#include <prefix.h>

DXBuffer::DXBuffer(BUFFER_TYPE type, const void* data, UINT elementSize, UINT count)
	: fElementSize(elementSize), fCount(count), fType(type)
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
	case BUFFER_TYPE_CONSTANT_BUFFER:
		bindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = fElementSize * fCount;
	bd.BindFlags = bindFlags;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.StructureByteStride = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA ms;
	ms.pSysMem = data;
	DXContext::sInstance.GetDevice()->CreateBuffer(&bd, &ms, &fpBuffer);
}

DXBuffer::~DXBuffer()
{
	fpBuffer->Release();
}

void DXBuffer::UpdateData(const void* data, UINT elementSize, UINT count)
{
	if (sizeof(data) > (fCount * fElementSize))
	{
		MessageBox(NULL, "Data size to big for the Buffer!", "Buffer ERROR!", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	DXContext::sInstance.GetDeviceContext()->UpdateSubresource(fpBuffer, 0, NULL, data, 0, 0);
}

void DXBuffer::Bind()
{
	UINT offset = 0;
	if (fType == BUFFER_TYPE_CONSTANT_BUFFER)
	{
		DXContext::sInstance.GetDeviceContext()->VSSetConstantBuffers(0u, 1u, &fpBuffer);
	}
	else
	{
		DXContext::sInstance.GetDeviceContext()->IASetVertexBuffers(0, 1, &fpBuffer, &fElementSize, &offset);
	}
}