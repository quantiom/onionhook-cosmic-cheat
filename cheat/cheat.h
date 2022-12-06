#pragma once
#include "../sdk/includes.h"
#include "../sdk/structs/header/c_game_instance.h"
#include <unordered_map>

namespace onionhook{
	namespace cheat {
		void hook();
		void unhook();

		inline bool m_stop_threads;

		inline HWND m_hwnd;
		inline WNDPROC m_wndproc;

		// global module handles
		inline HMODULE m_jvm_dll = nullptr;
		inline HMODULE m_opengl_dll = nullptr;
		inline HMODULE m_kernel32_dll = nullptr;

		// global handlers
		inline JNIEnv* m_jenv;
		inline JavaVM* m_jvm;

		inline c_game_instance* game;
	}

	namespace hooks {
		inline WNDPROC m_wndproc;
		//inline void* m_wgl_swap_buffers;

		//bool __stdcall wgl_swap_buffers(_In_ HDC hdc);
		long __stdcall wndproc(const HWND, unsigned int, uintptr_t, long);
	}
}