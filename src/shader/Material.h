#pragma once

class Material
{
private:
	struct ConstantBuffer
	{
		DirectX::XMMATRIX fProjectionMatrix;
	};
public:
	Material(const std::string& name);
	~Material();

	void Bind();
private:
	DXBuffer* fpConstantBuffer;
	ConstantBuffer* fpCbufData;
	ID3D11InputLayout* fpLayout;

	Shader<ID3D11VertexShader>* fpVertexShader;
	Shader<ID3D11PixelShader>* fpPixelShader;
};