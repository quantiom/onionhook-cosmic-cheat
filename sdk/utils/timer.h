#pragma once
#include <Windows.h>

namespace onionhook {
	class c_onion_timer {
	public:
		c_onion_timer() {}

		inline void reset() {
			this->m_time = GetTickCount64();
		}

		inline bool has_passed(long ms) {
			return (GetTickCount64() - m_time > ms);
		}

	private:
		unsigned long long m_time;
	};
}