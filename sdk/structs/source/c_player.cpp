#include "../header/c_player.h"
#include "../header/c_game_instance.h"

namespace onionhook {
	bool c_player::is_local_player() {
		return this->get_id() == this->m_game->get_player().get_id();
	}
}