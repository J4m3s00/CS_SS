#pragma once

class Material
{
public:
	Material(const std::string& name);
	~Material();
private:
	Shader<ID3D11VertexShader>* fpVertexShader;
	Shader<ID3D11PixelShader>* fpPixelShader;
};