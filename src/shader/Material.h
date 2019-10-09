#pragma once

class Material
{
public:
	Material(const std::string& name);
	~Material();

	virtual void Bind();
	virtual ID3D11InputLayout* GetLayout() const = 0;
protected:
	Shader<ID3D11VertexShader>* fpVertexShader;
	Shader<ID3D11PixelShader>* fpPixelShader;
};

class MaterialBasic : public Material
{
private:
	struct ConstantBuffer
	{
		DirectX::XMMATRIX fProjectionMatrix;
	};
public:
	MaterialBasic();
	~MaterialBasic();

	virtual ID3D11InputLayout* GetLayout() const { return fpLayout; }
	virtual void Bind() override;
private:
	ID3D11InputLayout* fpLayout;
	ConstantBuffer* fpCbufData;

	DXBuffer* fpConstantBuffer;
};