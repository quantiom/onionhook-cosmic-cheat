#pragma once

namespace logger {
	// colors don't seem to work in the java console thing

	template <typename ...Args>
	inline void log(Args&& ...args) {
		std::ostringstream ss{};
		(ss << ... << std::forward<Args>(args));

		std::cout << "[onionhook] " << ss.str() << std::endl;
	}
}