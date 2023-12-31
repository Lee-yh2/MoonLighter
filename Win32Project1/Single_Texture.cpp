#include "stdafx.h"
#include "Single_Texture.h"
#include "Graphic_Device.h"


CSingle_Texture::CSingle_Texture()
{
}


CSingle_Texture::~CSingle_Texture()
{
	Release_Texture();
}

HRESULT CSingle_Texture::Insert_Texture(const wstring & wstrFilePaht, const wstring & wstrStateKey, const int & iCount)
{
	ZeroMemory(&m_tTexInfo, sizeof(TEXINFO));
	

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePaht.c_str(), &m_tTexInfo.tImageInfo)))
	{
		wstring wstrErr = wstrFilePaht + L"LoadFailed";
		ERR_MSG(wstrErr.c_str());
		return E_FAIL;
	}
	if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
		wstrFilePaht.c_str(),
		m_tTexInfo.tImageInfo.Width,
		m_tTexInfo.tImageInfo.Height,
		m_tTexInfo.tImageInfo.MipLevels,
		0,
		m_tTexInfo.tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr, nullptr,
		&m_tTexInfo.pTexture)))
	{
		wstring wstrErr = wstrFilePaht + L"LoadFailed";
		ERR_MSG(wstrErr.c_str());
		return E_FAIL;
	}
	return S_OK;
}

const TEXINFO * CSingle_Texture::Get_Texture(const wstring & wstrStateKey, const int & iCount)
{
	return &m_tTexInfo;
}

void CSingle_Texture::Release_Texture()
{
	if (m_tTexInfo.pTexture)
		m_tTexInfo.pTexture->Release();
}
