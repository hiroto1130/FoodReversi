#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <d3d9.h>

#include "../Utility/RectSize.h"

using Utility::RectSize;

namespace Library
{
	class WindowParameter
	{
	public:

		static inline void GetInstanceHandle(HINSTANCE* pHInstance)
		{
			*pHInstance = hInst;
		}

		static inline void SetInstanceHandle(const HINSTANCE& hInstance)
		{
			hInst = hInstance;
		}

		static inline void GetWindowHandle(HWND* hwnd)
		{
			*hwnd = hWnd;
		}

		static inline void SetWindowHandle(const HWND& hwnd)
		{
			hWnd = hwnd;
		}

		static inline void GetRectSize(RectSize* rectSize)
		{
			*rectSize = window_size;
		}

		static inline void SetRectSize(const RectSize& rectSize)
		{
			window_size = rectSize;
		}

	private:
		static HINSTANCE hInst;

		static HWND hWnd;

		static RectSize window_size;

	};

	class Window
	{
	public:
		Window(const LPCSTR window_name)
		{
			Initialize(window_name);
		}

		BOOL Cenerate();

	private:

		WNDCLASSEX  wndclass;

		RectSize WindowSize{ 0,0 };

		VOID Initialize(const LPCSTR window_name);

		static LRESULT CALLBACK WndProc(HWND hWNd, UINT iMsg, WPARAM wParam, LPARAM lParam);

	};

}

#endif
