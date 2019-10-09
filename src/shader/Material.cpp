#include <prefix.h>

Material::Material(const std::string& name)
{
	fpVertexShader = new Shader<ID3D11VertexShader>("src/shader/" + name + ".hlsl");
	fpPixelShader = new Shader<ID3D11PixelShader>("src/shader/" + name + ".hlsl");

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

	fpConstantBuffer->Bind();
}