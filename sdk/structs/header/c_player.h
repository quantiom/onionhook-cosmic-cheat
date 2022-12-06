#pragma once
#include "c_entity.h"

namespace onionhook {
	class c_player : public c_entity {
	public:
		c_player(jobject javaclass, JNIEnv* env, c_game_instance* game)
			: c_entity(javaclass, env, game) {};

		bool is_local_player();
	};
}