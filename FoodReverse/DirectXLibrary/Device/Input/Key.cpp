#include "Key.h"

namespace Library
{

	BOOL Key::Initialize()
	{
		if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDinput, NULL)))
		{
			return FALSE;
		}

		if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pkey, NULL)))
		{
			return FALSE;
		}

		if (FAILED(pkey->SetDataFormat(&c_dfDIKeyboard)))
		{
			return FALSE;
		}

		HWND hInst;
		WindowParameter::GetWindowHandle(&hInst);

		if (FAILED(pkey->SetCooperativeLevel(hInst, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
		{
			return FALSE;
		}

		return TRUE;

	}

	void Key::UpdateKeyStatus()
	{
		using namespace KeyParameter;

		pkey->Acquire();
		for (int i = 0; i < KEY_MAX; ++i)
		{
			OldKeyState[i] = NowKeyState[i];
		}
		pkey->GetDeviceState(sizeof(NowKeyState), NowKeyState);

		bool isInputtedPrev = false;
		bool isInputted = false;

		ZeroMemory(m_details, sizeof(bool) * KEY_MAX);

		for (int i = 0; i < KEY_MAX; ++i)
		{
			isInputtedPrev = IsInputted(OldKeyState[i]);
			isInputted = IsInputted(NowKeyState[i]); // 今押されたキー

			if (isInputtedPrev)
			{
				m_details[i] = (isInputted) ? Input_State::IND_HOLD : Input_State::IND_RELEASE;

				continue;
			}

			m_details[i] = (isInputted) ? Input_State::IND_PRESS : Input_State::IND_NEUTRAL;
		}
	}
}
