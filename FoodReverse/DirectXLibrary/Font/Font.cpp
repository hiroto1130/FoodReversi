#include "Font.h"

namespace Library
{
	HRESULT Font::Initialize(int font_size)
	{
		//文字列レンダリングの初期化
		HFONT hFont;
		if (NULL == (hFont = CreateFont(0, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "メイリオ")))
		{
			return E_FAIL;
		}

		//文字列フォントの設定
		LPDIRECT3DDEVICE9 pDevice;
		Device::GetWindowHandle(&pDevice);

		if (FAILED(D3DXCreateFont(pDevice, font_size, font_size / 2, FW_BOLD, NULL, FALSE,
			SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN,
			"メイリオ", &pFont)))
		{
			return E_FAIL;
		}
	}


	//文字列レンダリング関数
	void Font::Rendering(LPCSTR szStr, INT iX, INT iY)
	{
		RECT rect = { iX, iY, 0, 0 }; //表示領域

		LPDIRECT3DDEVICE9 pDevice;
		Device::GetWindowHandle(&pDevice);

		pDevice->BeginScene();

		//文字列サイズを計算
		pFont->DrawText(
			NULL,
			szStr,
			-1,             //表示サイズ(-1で勝手に計算してくれる)
			&rect,          //表示範囲
			DT_CALCRECT,    //表示範囲に調整
			NULL);

		//そのサイズでレンダリング
		pFont->DrawText(
			NULL,
			szStr,
			-1,                     //表示サイズ(-1で全部)
			&rect,                  //表示範囲
			DT_LEFT | DT_BOTTOM,    //左詰めで両端揃え
			0xff00ff00);            //色

		pDevice->EndScene();
		pDevice->Present(NULL, NULL, NULL, NULL);

	}

}