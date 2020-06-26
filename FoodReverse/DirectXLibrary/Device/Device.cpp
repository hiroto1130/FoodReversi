#include "Device.h"

namespace Library
{

	LPDIRECT3DDEVICE9 Device::pDevice = nullptr;

	bool Device::DrawStart()
	{
		pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0f, 0);

		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		if (D3D_OK == pDevice->BeginScene())
		{
			return true;
		}

		return false;
	}

	void Device::DrawEnd()
	{
		pDevice->EndScene();
		pDevice->Present(NULL, NULL, NULL, NULL);
	}


	void Device::Clear()
	{
		pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(100, 100, 100), 1.0f, 0);
	}

	void Device::Present()
	{
		pDevice->Present(NULL, NULL, NULL, NULL);
	}

	HRESULT Device::Initialize()
	{
		//// InitD3d が初期化されているかどうか ////

		HWND hWnd = nullptr;
		WindowParameter::GetWindowHandle(&hWnd);

		if (NULL == (pDirect3d = Direct3DCreate9(D3D_SDK_VERSION)))
		{
			return E_FAIL;
		}

		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed = true;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


		//// InitDinput 初期化されているかどうか ////
		HRESULT result;
		if (S_OK != pDirect3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &pDevice))
		{
			return E_FAIL;
		}

		return S_OK;
	}

}
