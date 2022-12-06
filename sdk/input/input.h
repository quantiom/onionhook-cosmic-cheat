#pragma once
#include <string>
#include <Windows.h>
#include <deque>

namespace onionhook::input {
	enum class keystate {
		released,
		pressed,
		held,
		key_up,
		num_keystates
	};

	inline WNDPROC m_old_wndproc;
	inline bool m_is_copy = false;
	inline int scroll_amount;

	void update();

	keystate get_key_state(uint8_t keycode);
	vec2_t get_mouse_position();
	vec2_t get_mouse_offset();
	void clear_key_state(uint8_t keycode);

	void on_key_down(uint8_t keycode);
	void on_key_up(uint8_t keycode);
	void on_char(wchar_t c);

	inline WNDPROC get_old_wndproc() { return m_old_wndproc; }

	struct c_data {
		bool m_keyboard[256];
		std::wstring m_chars;
		vec2_t m_mouse_position;
	};

	inline c_data m_current_data,
		m_previous_data,
		m_queued_data;
}