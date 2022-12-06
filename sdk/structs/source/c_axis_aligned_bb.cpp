#include "../header/c_axis_aligned_bb.h"
#include "../../utils/vec.h"
#include "../../mappings.h"

namespace onionhook {
	vec3_t c_axis_aligned_bb::get_min() {
		return vec3_t{ this->get_min_x(), this->get_min_y(), this->get_min_z() };
	}

	vec3_t c_axis_aligned_bb::get_max() {
		return vec3_t{ this->get_max_x(), this->get_max_y(), this->get_max_z() };
	}

	void c_axis_aligned_bb::set_min(vec3_t min) {
		const auto min_x_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "minX");
		const auto min_x_field_id = this->get_field_id(min_x_field_mapping.m_name, min_x_field_mapping.m_signature);

		const auto min_y_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "minY");
		const auto min_y_field_id = this->get_field_id(min_y_field_mapping.m_name, min_y_field_mapping.m_signature);

		const auto min_z_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "minZ");
		const auto min_z_field_id = this->get_field_id(min_z_field_mapping.m_name, min_z_field_mapping.m_signature);

		this->m_env->SetDoubleField(this->m_object, min_x_field_id, min.x);
		this->m_env->SetDoubleField(this->m_object, min_y_field_id, min.y);
		this->m_env->SetDoubleField(this->m_object, min_z_field_id, min.z);
	}

	void c_axis_aligned_bb::set_max(vec3_t max) {
		const auto max_x_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "maxX");
		const auto max_x_field_id = this->get_field_id(max_x_field_mapping.m_name, max_x_field_mapping.m_signature);

		const auto max_y_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "maxY");
		const auto max_y_field_id = this->get_field_id(max_y_field_mapping.m_name, max_y_field_mapping.m_signature);

		const auto max_z_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "maxZ");
		const auto max_z_field_id = this->get_field_id(max_z_field_mapping.m_name, max_z_field_mapping.m_signature);

		this->m_env->SetDoubleField(this->m_object, max_x_field_id, max.x);
		this->m_env->SetDoubleField(this->m_object, max_y_field_id, max.y);
		this->m_env->SetDoubleField(this->m_object, max_z_field_id, max.z);
	}

	float c_axis_aligned_bb::get_min_x() {
		const auto min_x_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "minX");
		const auto min_x_field_id = this->get_field_id(min_x_field_mapping.m_name, min_x_field_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, min_x_field_id);
	}

	float c_axis_aligned_bb::get_min_y() {
		const auto min_y_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "minY");
		const auto min_y_field_id = this->get_field_id(min_y_field_mapping.m_name, min_y_field_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, min_y_field_id);
	}

	float c_axis_aligned_bb::get_min_z() {
		const auto min_z_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "minZ");
		const auto min_z_field_id = this->get_field_id(min_z_field_mapping.m_name, min_z_field_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, min_z_field_id);
	}

	float c_axis_aligned_bb::get_max_x() {
		const auto max_x_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "maxX");
		const auto max_x_field_id = this->get_field_id(max_x_field_mapping.m_name, max_x_field_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, max_x_field_id);
	}

	float c_axis_aligned_bb::get_max_y() {
		const auto max_y_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "maxY");
		const auto max_y_field_id = this->get_field_id(max_y_field_mapping.m_name, max_y_field_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, max_y_field_id);
	}

	float c_axis_aligned_bb::get_max_z() {
		const auto max_z_field_mapping = mappings::get_field_mapping("AxisAlignedBB", "maxZ");
		const auto max_z_field_id = this->get_field_id(max_z_field_mapping.m_name, max_z_field_mapping.m_signature);

		return this->m_env->GetDoubleField(this->m_object, max_z_field_id);
	}
}