#pragma once
#include <stdint.h>

namespace owd
{
	static constexpr uint8_t key_press		= 0;
	static constexpr uint8_t key_release	= 1;
	static constexpr uint8_t key_idle		= 2;

	/// <summary>
	/// Left mouse button.
	/// </summary>
	static constexpr int32_t LMB = 0;

	double mouse_x();
	double mouse_y();

	static constexpr int32_t key_arrow_up		= 265;
	static constexpr int32_t key_arrow_down		= 264;
	static constexpr int32_t key_arrow_left		= 263;
	static constexpr int32_t key_arrow_right	= 262;
	static constexpr int32_t key_enter			= 257;
	static constexpr int32_t key_backspace		= 259;

	struct s_key
	{
		int32_t	key		= 0;
		uint8_t	state	= key_idle;
	};

	s_key get_key(int32_t key_code);
	void set_key_idle(int32_t key_code);
}