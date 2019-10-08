#pragma once

template <typename ShaderType>
class Shader
{
public:
	Shader(const std::string& path)
	{
		MessageBox(NULL, "Unknown Shader Type!", "Shader ERROR!", MB_OK | MB_ICONEXCLAMATION);
	}
	~Shader() {}

	void Bind() {}
	ID3D10Blob* GetBlob() const { return NULL; }
};

template <>
class Shader<ID3D11VertexShader>
{
public:
	Shader(const std::string& path)
	{
		D3DX11CompileFromFile(path.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &fpBlob, 0, 0);
		DXContext::sInstance.GetDevice()->CreateVertexShader(fpBlob->GetBufferPointer(), fpBlob->GetBufferSize(), NULL, &fpShader);
	}

	~Shader()
	{
		fpShader->Release();
	}

	void Bind()
	{
		DXContext::sInstance.GetDeviceContext()->VSSetShader(fpShader, 0, 0);
	}

	ID3D10Blob* GetBlob() const { return fpBlob; }
private:
	ID3D11VertexShader* fpShader;
	ID3D10Blob* fpBlob;
};

template <>
class Shader<ID3D11PixelShader>
{
public:
	Shader(const std::string& path)
	{
		D3DX11CompileFromFile(path.c_str() , 0, 0, "PShader", "ps_4_0", 0, 0, 0, &fpBlob, 0, 0);
		DXContext::sInstance.GetDevice()->CreatePixelShader(fpBlob->GetBufferPointer(), fpBlob->GetBufferSize(), NULL, &fpShader);
	}

	~Shader()
	{
		fpShader->Release();
	}

	void Bind()
	{
		DXContext::sInstance.GetDeviceContext()->PSSetShader(fpShader, 0, 0);
	}

	ID3D10Blob* GetBlob() const { return fpBlob; }
private:
	ID3D11PixelShader* fpShader;
	ID3D10Blob* fpBlob;
};