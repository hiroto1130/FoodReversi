#include "Window.h"

namespace Library
{

	HINSTANCE WindowParameter::hInst = nullptr;
	HWND WindowParameter::hWnd = nullptr;
	RectSize WindowParameter::window_size{0,0};

	VOID Window::Initialize(const LPCSTR window_name)
	{
		HINSTANCE hInst = nullptr;
		WindowParameter::GetInstanceHandle(&hInst);

		wndclass.cbSize = sizeof(wndclass);
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInst;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = window_name;
		wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		RegisterClassEx(&wndclass);

		hInst = GetModuleHandle(nullptr);

	}

	BOOL Window::Cenerate()
	{
		HWND hWnd = nullptr;
		WindowParameter::GetWindowHandle(&hWnd);

		RectSize window_size{ 0,0 };
		WindowParameter::GetRectSize(&window_size);

		hWnd = CreateWindow(wndclass.lpszClassName, wndclass.lpszClassName, WS_OVERLAPPEDWINDOW, 0, 0, window_size.width, window_size.height, NULL, NULL, wndclass.hInstance, NULL);

		WindowParameter::SetWindowHandle(hWnd);

		if (hWnd == NULL)
		{
			return FALSE;
		}

		RECT rx; //ウィンドウ領域
		RECT cx; //クライアント領域
		GetWindowRect(hWnd, &rx);
		GetClientRect(hWnd, &cx);
		const int new_width = window_size.width + (rx.right - rx.left) - (cx.right - cx.left);
		const int new_height = window_size.height + (rx.bottom - rx.top) - (cx.bottom - cx.top);
		const int disp_width = GetSystemMetrics(SM_CXSCREEN);
		const int disp_height = GetSystemMetrics(SM_CYSCREEN);
		SetWindowPos(hWnd, NULL, (disp_width - new_width) / 2,
			(disp_height - new_height) / 2,
			new_width, new_height, SWP_SHOWWINDOW);

		ShowWindow(hWnd, SW_SHOW);
		UpdateWindow(hWnd);

		return TRUE;
	}

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (iMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
		}

		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}
}
