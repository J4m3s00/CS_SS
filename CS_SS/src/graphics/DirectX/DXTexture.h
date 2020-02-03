#pragma once


class DXTexture
{
public:
	DXTexture(const std::string& filePath);
	~DXTexture();

	void Bind();
private:
	ID3D11ShaderResourceView* fpTextureView;
};