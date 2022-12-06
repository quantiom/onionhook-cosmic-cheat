#include <windowsx.h>
#include "../../sdk/includes.h"
#include "../../sdk/input/input.h"
#include "../cheat.h"

namespace onionhook::hooks {
	long __stdcall hooks::wndproc(HWND hwnd, unsigned int message, uintptr_t w_param, long l_param) {
		const auto x_pos = GET_X_LPARAM(l_param);
		const auto y_pos = GET_Y_LPARAM(l_param);
		
		switch (message) {
		case WM_KEYDOWN:
			input::on_key_down(w_param);
			break;
		case WM_KEYUP:
			input::on_key_up(w_param);
			break;
		case WM_LBUTTONDOWN:
			input::on_key_down(VK_LBUTTON);
			break;
		case WM_LBUTTONUP:
			input::on_key_up(VK_LBUTTON);
			break;
		case WM_CHAR:
			input::on_char(w_param);
			break;
		case WM_RBUTTONDOWN:
			input::on_key_down(VK_RBUTTON);
			break;
		case WM_RBUTTONUP:
			input::on_key_up(VK_RBUTTON);
			break;
		case WM_XBUTTONDOWN:
			if (GET_XBUTTON_WPARAM(w_param) == 1)
				input::on_key_down(VK_XBUTTON1);
			else
				input::on_key_down(VK_XBUTTON2);
			break;
		case WM_XBUTTONUP:
			if (GET_XBUTTON_WPARAM(w_param) == 1)
				input::on_key_up(VK_XBUTTON1);
			else
				input::on_key_up(VK_XBUTTON2);
			break;
		case WM_MBUTTONDOWN:
			input::on_key_down(VK_MBUTTON);
			break;
		case WM_MBUTTONUP:
			input::on_key_up(VK_MBUTTON);
			break;
		case WM_MOUSEWHEEL:
			input::scroll_amount = int(float(GET_WHEEL_DELTA_WPARAM(w_param)) / float(WHEEL_DELTA));
			break;
		}

		return CallWindowProcA(cheat::m_wndproc, hwnd, message, w_param, l_param);
	}
}