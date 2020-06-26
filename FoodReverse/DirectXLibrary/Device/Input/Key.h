#ifndef KEY_H
#define KEY_H

#include <dinput.h>

#include "../Device.h"

namespace Library
{
	namespace KeyParameter
	{
		static const int KEY_MAX = 256;

		static BYTE NowKeyState[KEY_MAX] = { 0 };
		static BYTE OldKeyState[KEY_MAX] = { 0 };

		enum class Input_State
		{
			//押された瞬間のフレームだけtrue
			IND_PRESS,

			//押され続けられている間true
			IND_HOLD,

			//離された瞬間のフレームだけtrue
			IND_RELEASE,

			//前回と現在のフレームで押されていない間true
			IND_NEUTRAL,
			IND_MAX
		};
	};

	class Key
	{
	public:
		Key() { Initialize(); }

		inline bool IsPressed(int key) const
		{
			return (m_details[key] == KeyParameter::Input_State::IND_PRESS);
		}

		inline bool IsHeld(int key) const
		{
			return (m_details[key] == KeyParameter::Input_State::IND_HOLD);
		}

		inline bool IsReleased(int key) const
		{
			return (m_details[key] == KeyParameter::Input_State::IND_RELEASE);
		}

		inline bool IsNeutral(int key) const
		{
			return (m_details[key] == KeyParameter::Input_State::IND_NEUTRAL);
		}

		void UpdateKeyStatus();

	private:

		inline bool IsInputted(int key) const
		{
			return ((key & 0x80) != 0);
		}

		BOOL Initialize();
		LPDIRECTINPUT8 pDinput;
		LPDIRECTINPUTDEVICE8 pkey;

		KeyParameter::Input_State m_details[KeyParameter::KEY_MAX];

	};

}

#endif

