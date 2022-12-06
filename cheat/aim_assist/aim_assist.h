#pragma once
#include "../../sdk/structs/header/c_player.h"
#include <optional>

namespace onionhook::aim_assist {
	void run();
	std::optional<c_player> get_best_player();
}