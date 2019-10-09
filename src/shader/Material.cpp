#include <prefix.h>

Material::Material(const std::string& name)
{
	fpVertexShader = new Shader<ID3D11VertexShader>("src/shader/" + name + ".hlsl");
	fpPixelShader = new Shader<ID3D11PixelShader>("src/shader/" + name + ".hlsl");

	D3D11_INPUT_ELEMENT_DESC inputDescription[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	DXContext::sInstance.GetDevice()->CreateInputLayout(inputDescription, 2, fpVertexShader->GetBlob()->GetBufferPointer(), fpVertexShader->GetBlob()->GetBufferSize(), &fpLayout);


	fpCbufData = new ConstantBuffer();
	fpCbufData->fProjectionMatrix = DirectX::XMMatrixTranspose( DirectX::XMMatrixPerspectiveFovLH(60.0f, 16.0f/9.0f, 0.00001f, 100000.0f)) ;

	fpConstantBuffer = new DXBuffer(BUFFER_TYPE_CONSTANT_BUFFER, (const void*)fpCbufData, sizeof(ConstantBuffer), 1);
}

Material::~Material()
{
	delete fpConstantBuffer;

	delete fpVertexShader;
	delete fpPixelShader;
}

void Material::Bind()
{
	fpVertexShader->Bind(); 
	fpPixelShader->Bind();

	DXContext::sInstance.GetDeviceContext()->IASetInputLayout(fpLayout);

	fpConstantBuffer->Bind();
}