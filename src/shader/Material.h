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
public:
	struct ConstantBuffer
	{
		glm::mat4 fProjectionMatrix;
		glm::mat4 fModelMatrix;
	};
public:
	MaterialBasic();
	~MaterialBasic();

	ConstantBuffer* GetConstantBuffer() { return fpCbufData; }

	virtual ID3D11InputLayout* GetLayout() const { return fpLayout; }
	virtual void Bind() override;
private:
	ID3D11InputLayout* fpLayout;
	ConstantBuffer* fpCbufData;

	DXBuffer* fpConstantBuffer;
	DXTexture* fpTexture;
};