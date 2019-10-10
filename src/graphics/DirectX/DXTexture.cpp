#include <prefix.h>

DXTexture::DXTexture(const std::string& filePath)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = nullptr;
	fif = FreeImage_GetFileType(filePath.c_str(), 0);
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filePath.c_str());
	if (fif == FIF_UNKNOWN)
	{
		MessageBox(NULL, "Texture ERROR!", "Unknown texture format or unknown file!", MB_OK | MB_ICONWARNING);
		return;
	}

	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filePath.c_str());

	if (!dib)
	{
		MessageBox(NULL, "Texture ERROR!", "Image file is corrupt!", MB_OK | MB_ICONWARNING);
		return;
	}

	FIBITMAP* bitmap = FreeImage_ConvertTo32Bits(dib);
	FreeImage_Unload(dib);

	unsigned char* pixels = FreeImage_GetBits(bitmap);
	UINT width = FreeImage_GetWidth(bitmap);
	UINT height = FreeImage_GetHeight(bitmap);
	UINT bits = FreeImage_GetBPP(bitmap);

	int size = width * height * (bits / 8);
	unsigned char* IMAGE_DATA = new unsigned char[size];
	memcpy(IMAGE_DATA, pixels, size);
	FreeImage_Unload(bitmap);

	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = IMAGE_DATA;
	sd.SysMemPitch = width * (bits / 8);
	ID3D11Texture2D* pTexture;
	DXContext::sInstance.GetDevice()->CreateTexture2D(&textureDesc, &sd, &pTexture);


	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	DXContext::sInstance.GetDevice()->CreateShaderResourceView(pTexture, &srvDesc, &fpTextureView);

	//TODO: release texture
}

DXTexture::~DXTexture()
{
	fpTextureView->Release();
}

void DXTexture::Bind()
{
	DXContext::sInstance.GetDeviceContext()->PSSetShaderResources(0, 1, &fpTextureView);
}