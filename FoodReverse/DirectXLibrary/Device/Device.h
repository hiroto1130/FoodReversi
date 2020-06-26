#ifndef DEVICE_H
#define DEVICE_H

#include <windows.h>
#include <d3d9.h>

#include "../Winodw/Window.h"

namespace Library
{

	class Device
	{
	public:
		Device() { Initialize(); }
		virtual ~Device() {}

		static inline void GetWindowHandle(LPDIRECT3DDEVICE9* Device)
		{
			*Device = pDevice;
		}

		static inline void SetWindowHandle(const LPDIRECT3DDEVICE9& Device)
		{
			pDevice = Device;
		}

		bool DrawStart();

		void DrawEnd();

		void Clear();

		void Present();

	private:

		LPDIRECT3D9 pDirect3d;
		static LPDIRECT3DDEVICE9 pDevice;
		D3DPRESENT_PARAMETERS d3dpp;

		HRESULT Initialize();


	};

}

#endif
