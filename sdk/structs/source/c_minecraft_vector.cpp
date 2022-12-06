#include "../header/c_minecraft_vector.h"
#include "../header/c_game_instance.h"

namespace onionhook {
	c_minecraft_vector c_minecraft_vector::from_vec3(vec3_t in, JNIEnv* env, c_game_instance* game) {
		jclass vector_class = game->m_class_handler->get_class(mappings::get_class_name_mapping("Vec3").m_name);
		jmethodID constructor = env->GetMethodID(vector_class, "<init>", "(DDD)V");
		jobject object = env->NewObject(vector_class, constructor, (double)in.x, (double)in.y, (double)in.z);

		return c_minecraft_vector(object, env, game);
	}
}