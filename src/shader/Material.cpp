#include <prefix.h>

Material::Material(const std::string& name)
{
	fpVertexShader = new Shader<ID3D11VertexShader>("src/shader/Basic.hlsl");
	fpPixelShader = new Shader<ID3D11PixelShader>("src/shader/Basic.hlsl");
}

Material::~Material()
{

}