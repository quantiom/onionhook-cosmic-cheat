#include "cheat.h"
#include "reach/reach.h"
#include "aim_assist/aim_assist.h"

#include "../sdk/input/input.h"

namespace onionhook::cheat {
	int __stdcall enum_windows(HWND hWnd, LPARAM lParam) {
		unsigned long pid;
		GetWindowThreadProcessId(hWnd, &pid);

		if (GetProcessId(GetCurrentProcess()) == pid) {
			m_hwnd = hWnd;
			return false;
		}

		return true;
	}

	void hook() {
		// wait for JVM
		while (!(m_jvm_dll = GetModuleHandleA(xor("jvm.dll")))) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		while (!(m_opengl_dll = GetModuleHandleA(xor("opengl32.dll")))) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		while (!(m_kernel32_dll = GetModuleHandleA(xor("Kernel32.dll")))) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		// get HWND
		EnumWindows(enum_windows, NULL);

		// alloc console (after getting hwnd)
		AllocConsole();

		SetConsoleTitleW(L"onionhook v4");
		freopen_s(reinterpret_cast<FILE**>stdin, "CONIN$", "r", stdin);
		freopen_s(reinterpret_cast<FILE**>stdout, "CONOUT$", "w", stdout);

		// get the jvm and jni enviroment
		jsize count;
		if (JNI_GetCreatedJavaVMs(&m_jvm, 1, &count) != JNI_OK || count == 0) {
			return;
		}

		jint res = m_jvm->GetEnv((void**)&m_jenv, JNI_VERSION_1_6);
		if (res == JNI_EDETACHED) {
			res = m_jvm->AttachCurrentThread((void**)&m_jenv, nullptr);
		}

		if (res != JNI_OK) {
			return;
		}

		// setup mappings
		mappings::setup_mappings();

		// start hooking
		m_wndproc = (WNDPROC)SetWindowLongPtrA(m_hwnd, GWLP_WNDPROC, (LONG_PTR)hooks::wndproc);

		// initialize game instance and class handler
		game = new c_game_instance(m_jenv, new c_class_handler(m_jenv));
		
		logger::log("Initialized.");

		// main loop
		while (!GetAsyncKeyState(VK_END)) {
			input::update();

			if (game->get_player().is_valid()) {
				reach::run(); // reach
				aim_assist::run(); // aim assist
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}

	void unhook() {
		// replace with original wndproc
		SetWindowLongPtrA(m_hwnd, GWLP_WNDPROC, (LONG_PTR)m_wndproc);

		//class_handler::free_global_refs();

		Sleep(500);

		m_jvm->DetachCurrentThread();
	}
}