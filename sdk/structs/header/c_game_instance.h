#pragma once
#include "c_entity.h"
#include "c_world.h"
#include "c_class_handler.h"

namespace onionhook {
	class c_game_instance {
	public:
		c_game_instance(JNIEnv* env, c_class_handler* class_handler) : m_env(env), m_class_handler(class_handler) {
			this->m_class_handler->setup_class_loader();
		};

		jobject get_minecraft();
		c_entity get_player();
		c_world get_world();

		bool has_focus();

		c_class_handler* m_class_handler;

	private:
		JNIEnv* m_env;
	};
}