#ifndef FONT_H
#define FONT_H

#include<d3dx9.h>
#include"../Device/Device.h"

namespace Library
{
	class Font
	{
	public:

		Font(int fonst_size) { Initialize(fonst_size); }

		void Rendering(LPCSTR szStr, INT iX, INT iY);

	private:

		HRESULT Initialize(int fonst_size);

		LPD3DXFONT pFont;
	};
}

#endif
