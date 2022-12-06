#include "../../cheat/cheat.h"
#include "input.h"

namespace onionhook::input {
	void update() {
		m_previous_data = m_current_data;

		const auto window_handle = cheat::m_hwnd;

		// get client area
		RECT client_size;
		GetClientRect(window_handle, &client_size);
		const auto screen_width = client_size.right - client_size.left,
			screen_height = client_size.bottom - client_size.top;

		// get mouse position
		POINT mouse_position;
		GetCursorPos(&mouse_position);
		ScreenToClient(window_handle, &mouse_position);

		// if mouse went out of client area
		if (mouse_position.x < 0L || mouse_position.x > screen_width || mouse_position.y < 0L || mouse_position.y > screen_height) {
			for (size_t i = 0; i < 256; i++)
				m_queued_data.m_keyboard[i] = false;

			// clamp mouse position to client area
			mouse_position.x = std::clamp(mouse_position.x, 0L, screen_width);
			mouse_position.y = std::clamp(mouse_position.y, 0L, screen_height);
		}

		m_queued_data.m_mouse_position = { float(mouse_position.x), float(mouse_position.y) };
		m_current_data = m_queued_data;

		m_queued_data.m_chars.clear();
	}

	keystate get_key_state(uint8_t keycode) {
		if (m_current_data.m_keyboard[keycode] && !m_previous_data.m_keyboard[keycode])
			return keystate::pressed;
		if (m_current_data.m_keyboard[keycode] && m_previous_data.m_keyboard[keycode])
			return keystate::held;
		if (!m_current_data.m_keyboard[keycode] && m_previous_data.m_keyboard[keycode])
			return keystate::released;

		return keystate::key_up;
	}

	vec2_t get_mouse_position() {
		return m_current_data.m_mouse_position;
	}

	vec2_t get_mouse_offset() {
		return m_current_data.m_mouse_position - m_previous_data.m_mouse_position;
	}

	void clear_key_state(uint8_t keycode) {
		m_current_data.m_keyboard[keycode] = false;
	}

	void on_key_down(uint8_t keycode) {
		m_queued_data.m_keyboard[keycode] = true;
	}

	void on_key_up(uint8_t keycode) {
		m_queued_data.m_keyboard[keycode] = false;
	}

	void on_char(wchar_t c) {
		m_queued_data.m_chars.push_back(c);
	}
}