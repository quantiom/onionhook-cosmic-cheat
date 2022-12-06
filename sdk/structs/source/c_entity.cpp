#include "../header/c_entity.h"
#include "../header/c_axis_aligned_bb.h"
#include "../../utils/vec.h"
#include "../../mappings.h"
#include "../../../cheat/cheat.h"

namespace onionhook {
	// EntitiyLivingBase#getHealth()
	int c_entity::get_health() {
		const auto get_health_mapping = mappings::get_method_mapping("EntityLivingBase", "getHealth");
		const auto get_health_method_id = this->get_method_id(get_health_mapping.m_name, get_health_mapping.m_signature);
		
		return this->m_env->CallFloatMethod(this->m_object, get_health_method_id);
	}

	bool c_entity::is_alive() {
		return this->get_health() > 0;
	}

	bool c_entity::is_valid() {
		return this->m_object != nullptr && this->is_alive();
	}

	vec3_t c_entity::get_angles() {
		return vec3_t{ this->get_yaw(), this->get_pitch(), 0.0f };
	}

	vec3_t c_entity::get_prev_angles() {
		return vec3_t{ this->get_prev_yaw(), this->get_prev_pitch(), 0.0f };
	}

	void c_entity::set_angles(vec3_t angles) {
		const auto previous = this->get_angles();

		// previous yaw & pitch
		const auto prev_yaw_mapping = mappings::get_field_mapping("Entity", "prevRotationYaw");
		const auto prev_pitch_mapping = mappings::get_field_mapping("Entity", "prevRotationPitch");

		this->m_env->SetFloatField(this->m_object, this->get_field_id(prev_yaw_mapping.m_name, prev_yaw_mapping.m_signature), previous.x);
		this->m_env->SetFloatField(this->m_object, this->get_field_id(prev_pitch_mapping.m_name, prev_pitch_mapping.m_signature), previous.y);

		// new yaw & pitch
		const auto yaw_mapping = mappings::get_field_mapping("Entity", "rotationYaw");
		const auto pitch_mapping = mappings::get_field_mapping("Entity", "rotationPitch");

		this->m_env->SetFloatField(this->m_object, this->get_field_id(yaw_mapping.m_name, yaw_mapping.m_signature), angles.x);
		this->m_env->SetFloatField(this->m_object, this->get_field_id(pitch_mapping.m_name, pitch_mapping.m_signature), angles.y);
	}

	vec3_t c_entity::get_position() {
		return vec3_t{ this->get_x(), this->get_y(), this->get_z() };
	}

	// Entity#getPositionEyes(partialTicks)
	c_minecraft_vector c_entity::get_eye_position() {
		const auto get_position_eyes_mapping = mappings::get_method_mapping("Entity", "getPositionEyes");

		return c_minecraft_vector(this->m_env->CallObjectMethod(this->m_object, this->get_method_id(get_position_eyes_mapping.m_name, get_position_eyes_mapping.m_signature), 1.0F), this->m_env, this->m_game);
	}

	// Entity#entityId
	int c_entity::get_id() {
		const auto id_field_mapping = mappings::get_field_mapping("Entity", "entityId");
		const auto field = this->m_env->GetFieldID(this->m_env->GetObjectClass(this->m_object), id_field_mapping.m_name.c_str(), id_field_mapping.m_signature.c_str());
		
		return this->m_env->GetIntField(this->m_object, field);
	}

	// Entity#posX
	float c_entity::get_x() {
		const auto x_pos_field_mapping = mappings::get_field_mapping("Entity", "posX");
		const auto x_pos_field = this->get_field_id(x_pos_field_mapping.m_name, x_pos_field_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, x_pos_field);
	}

	// Entity#posX
	float c_entity::get_y() {
		const auto pos_y_mapping = mappings::get_field_mapping("Entity", "posY");
		const auto y_pos_field = this->get_field_id(pos_y_mapping.m_name, pos_y_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, y_pos_field);
	}

	// Entity#posX
	float c_entity::get_z() {
		const auto pos_z_mapping = mappings::get_field_mapping("Entity", "posZ");
		const auto z_pos_field = this->get_field_id(pos_z_mapping.m_name, pos_z_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, z_pos_field);
	}

	// Entity#boundingBox
	c_axis_aligned_bb c_entity::get_bounding_box() {
		const auto bounding_box_mapping = mappings::get_field_mapping("Entity", "boundingBox");
		const auto bounding_box_field = this->get_field_id(bounding_box_mapping.m_name, bounding_box_mapping.m_signature);

		return c_axis_aligned_bb(this->m_env->GetObjectField(this->m_object, bounding_box_field), this->m_env, this->m_game);
	}
	
	// Entity#rotationYaw
	float c_entity::get_yaw() {
		const auto yaw_mapping = mappings::get_field_mapping("Entity", "rotationYaw");
		const auto yaw_field_id = this->get_field_id(yaw_mapping.m_name, yaw_mapping.m_signature);

		return this->m_env->GetFloatField(this->m_object, yaw_field_id);
	}
	
	// Entity#rotationPitch
	float c_entity::get_pitch() {
		const auto pitch_mapping = mappings::get_field_mapping("Entity", "rotationPitch");
		const auto pitch_field_id = this->get_field_id(pitch_mapping.m_name, pitch_mapping.m_signature);

		return this->m_env->GetFloatField(this->m_object, pitch_field_id);
	}

	// Entity#prevRotationYaw
	float c_entity::get_prev_yaw() {
		const auto yaw_mapping = mappings::get_field_mapping("Entity", "prevRotationYaw");
		const auto yaw_field_id = this->get_field_id(yaw_mapping.m_name, yaw_mapping.m_signature);

		return this->m_env->GetFloatField(this->m_object, yaw_field_id);
	}

	// Entity#prevRotationPitch
	float c_entity::get_prev_pitch() {
		const auto pitch_mapping = mappings::get_field_mapping("Entity", "prevRotationPitch");
		const auto pitch_field_id = this->get_field_id(pitch_mapping.m_name, pitch_mapping.m_signature);

		return this->m_env->GetFloatField(this->m_object, pitch_field_id);
	}
}