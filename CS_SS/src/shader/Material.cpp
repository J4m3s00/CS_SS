#include <prefix.h>

Material::Material(const std::string& name)
{

	fpVertexShader = new Shader<ID3D11VertexShader>(
#include "Basic.hlsl"
		, name
		);

	fpPixelShader = new Shader<ID3D11PixelShader>(
#include "Basic.hlsl"
		, name);
}

Material::~Material()
{
	delete fpVertexShader;
	delete fpPixelShader;
}

void Material::Bind()
{
	fpVertexShader->Bind(); 
	fpPixelShader->Bind();

}

//Basic Material
/////////////////////////////////////////////
MaterialBasic::MaterialBasic()
	: Material("Basic")
{
	D3D11_INPUT_ELEMENT_DESC inputDescription[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 3 * 2 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 3 * 2 * 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 3 * 2 * 3 * 3 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	DXContext::sInstance.GetDevice()->CreateInputLayout(inputDescription, 5, fpVertexShader->GetBlob()->GetBufferPointer(), fpVertexShader->GetBlob()->GetBufferSize(), &fpLayout);


	fpCbufData = new ConstantBuffer();
	fpCbufData->fProjectionMatrix = glm::perspectiveLH(60.0f, 1.0f / 2.0f, 0.001f, 10000.0f);
	fpCbufData->fProjectionMatrix = glm::transpose(fpCbufData->fProjectionMatrix);

	fpConstantBuffer = new DXBuffer(BUFFER_TYPE_CONSTANT_BUFFER, (const void*)fpCbufData, sizeof(ConstantBuffer), 1);

	fpTexture = new DXTexture("res/Test.png");
}

MaterialBasic::~MaterialBasic()
{
	delete fpConstantBuffer;
}

void MaterialBasic::Bind() 
{
	fpConstantBuffer->UpdateData((const void*)fpCbufData, sizeof(ConstantBuffer), 1);
	Material::Bind();
	fpTexture->Bind();
	DXContext::sInstance.GetDeviceContext()->IASetInputLayout(fpLayout);

	fpConstantBuffer->Bind();
}