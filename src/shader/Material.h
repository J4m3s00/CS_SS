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

	Shader<ID3D11VertexShader>* fpVertexShader;
	Shader<ID3D11PixelShader>* fpPixelShader;
};