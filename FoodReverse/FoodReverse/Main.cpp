#include <windows.h>
#include <d3d9.h>

#include "../DirectXLibrary/Winodw/Window.h"
#include "../DirectXLibrary/Device/Device.h"
#include "../DirectXLibrary/Device/Input/Key.h"

using namespace Library;
using namespace Utility;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, int iCmdShow)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	Window* window = new Window("Test");
	WindowParameter::SetRectSize(RectSize{ 640,480 });

	window->Cenerate();

	Device* device = new Device;
	Key* key = new Key;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			key->UpdateKeyStatus();
			device->DrawStart();





			device->DrawEnd();

		}
	}

	delete window;
	delete key;

	return (INT)msg.wParam;

}

