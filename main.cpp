#include "sdk/includes.h"
#include "cheat/cheat.h"

// forward declarations
void initialize();
HINSTANCE m_unhookinst;

bool __stdcall DllMain(HINSTANCE instance, unsigned long reason, void* reserved) {
	// reduce the size of the dll by removing DLL_THREAD* calls
	DisableThreadLibraryCalls(instance);

	switch (reason) {
		case DLL_PROCESS_ATTACH: {
			m_unhookinst = instance;
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)initialize, 0, 0, 0);
		} break;

		default: {

		} break;
	}

	return true;
}

void initialize() {
	onionhook::cheat::hook();
	onionhook::cheat::unhook();

	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
	FreeConsole();

	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(m_unhookinst, 0);
}