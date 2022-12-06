#pragma once
#include <iostream>
#include <unordered_map>
#include <algorithm>

namespace onionhook::mappings {
	struct class_name_mapping {
		class_name_mapping() {}

		class_name_mapping(std::string name) {
			this->m_name = name;
			this->m_descriptor = this->get_descriptor();
		}

		std::string m_name;
		std::string m_descriptor;

	private:
		// java.lang.Object = Ljava/lang/Object;
		inline std::string get_descriptor() {
			auto str = std::string(this->m_name);
			
			std::replace(str.begin(), str.end(), '.', '/');
			str.insert(0, "L");
			str.append(";");
		
			return str;
		}
	};

	struct method_mapping {
		std::string m_name;
		std::string m_signature;

		// argument position - value (these values are either byte, int, boolean, double, or long)
		std::unordered_map<int, long> encrypted_args{};
		int total_args = 0; // only set if using encrypted args
	};

	struct field_mapping {
		std::string m_name;
		std::string m_signature;
	};

	struct class_mapping {
		class_name_mapping m_class_name_mapping;
		std::unordered_map<std::string, method_mapping> m_method_mappings;
		std::unordered_map<std::string, field_mapping> m_field_mappings;
	};

	inline std::unordered_map<std::string, class_mapping> class_mappings;

	inline class_name_mapping get_class_name_mapping(const std::string& class_name) {
		return class_mappings.at(class_name).m_class_name_mapping;
	}

	inline method_mapping get_method_mapping(const std::string& class_name, const std::string& method_name) {
		return class_mappings.at(class_name).m_method_mappings[method_name];
	}

	inline field_mapping get_field_mapping(const std::string& class_name, const std::string& field_name) {
		return class_mappings.at(class_name).m_field_mappings[field_name];
	}

	inline std::string replace_placeholders(const std::string& input) {
		std::string ret_str {};

		std::string placeholder_text {};
		bool parsing_placeholder = false;

		for (const char& c : input) {
			if (c == '{') {
				parsing_placeholder = true;
			} else if (c == '}') {
				parsing_placeholder = false;

				std::string copied_name(class_mappings.at(placeholder_text).m_class_name_mapping.m_name);
				std::replace(copied_name.begin(), copied_name.end(), '.', '/');

				ret_str.append("L" + copied_name + ";");
				placeholder_text.clear();
			} else if (parsing_placeholder) {
				placeholder_text += c;
			} else {
				ret_str += c;
			}
		}

		return ret_str;
	}

	// Note: All these mappings are old since I have not touched this
	// project in over a year. If you want it to work, you will need to find
	// the new ones yourself.
	inline void setup_mappings() {
		// AxisAlignedBB
		class_mappings["AxisAlignedBB"] = class_mapping{
			class_name_mapping("net.minecraft.zS"), 
			{},
			{
				{ "minX", { "e", "D"} },
				{ "minY", { "b", "D"} },
				{ "minZ", { "d", "D"} },
				{ "maxX", { "f", "D"} },
				{ "maxY", { "g", "D"} },
				{ "maxZ", { "a", "D"} },
			}
		};

		// Entity
		class_mappings["Entity"] = class_mapping{
			class_name_mapping("net.minecraft.gY"),
			{
				{ "getPositionEyes", { "d", "(F){Vec3}" } }
			},
			{
				{ "posX", { "f", "D" } },
				{ "posY", { "af", "D" } },
				{ "posZ", { "an", "D" } },
				{ "rotationYaw", { "A", "F" } },
				{ "rotationPitch", { "a", "F" } },
				{ "prevRotationYaw", { "T", "F" } },
				{ "prevRotationPitch", { "N", "F" } },
				{ "boundingBox", { "am", "{AxisAlignedBB}" } },
				{ "entityId", { "ah", "I"} }
			}
		};

		// EntityLivingBase
		class_mappings["EntityLivingBase"] = class_mapping{
			class_name_mapping("net.minecraft.go"),
			{
				{ "getHealth", { "a", "()F" } }
			},
			{}
		};

		// EntityPlayer
		class_mappings["EntityPlayer"] = class_mapping{ class_name_mapping("net.minecraft.hd"), {}, {} };
	
		// EntityPlayerSP
		class_mappings["EntityPlayerSP"] = class_mapping{ class_name_mapping("net.minecraft.client.e9"), {}, {} };

		// Vec3
		class_mappings["Vec3"] = class_mapping{
			class_name_mapping("net.minecraft.db"),
			{},
			{
				{ "xCoord", { "c", "D" } },
				{ "yCoord", { "b", "D" } },
				{ "zCoord", { "a", "D" } }
			}
		};

		// MovingObjectPosition.MovingObjectType
		class_mappings["MovingObjectPosition.MovingObjectType"] = class_mapping{ class_name_mapping("net.minecraft.nW"), {}, {} };

		// MovingObjectPosition
		class_mappings["MovingObjectPosition"] = class_mapping{
			class_name_mapping("net.minecraft.tX"),
			{},
			{
				{ "typeOfHit", { "c", "{MovingObjectPosition.MovingObjectType}" } },
				{ "hitVec", { "a", "{Vec3}" } },
				{ "entityHit", { "d", "{Entity}" } }
			}
		};

		// WorldClient
		class_mappings["WorldClient"] = class_mapping{ 
			class_name_mapping("net.minecraft.client.lg"), 
			{},
			{
				{ "entityList", { "Q", "Ljava/util/Set;" } }
			} 
		};

		// World
		class_mappings["World"] = class_mapping{
			class_name_mapping("net.minecraft.AK"),
			{
				{ "rayTraceBlocks", {
						"a", "(I{Vec3}{Vec3}ZCZCZ){MovingObjectPosition}",
							{ // obfuscated args
								{ 0, 24360 },
								{ 1, 1 },
								{ 6, 12999479 }
							},
							8 // total args
					} 
				}
			},
			{
				{ "playerEntities", { "l", "Ljava/util/List;" } }
			}
		};

		// Minecraft
		class_mappings["Minecraft"] = class_mapping{
			class_name_mapping("net.minecraft.client.c7"), // Minecraft
			{
				{ "getMinecraft", { "am", "(){Minecraft}" } }
			},
			{
				{ "thePlayer", { "w", "{EntityPlayerSP}" } },
				{ "theWorld", { "a4", "{WorldClient}" } },
				{ "inGameHasFocus", { "a0", "Z" } }
			}
		};

		// replace class placeholders // {Object} (if it was in the mappings) would be replaced with Ljava/lang/Object;
		for (auto& [class_name, class_mappingz] : class_mappings) {
			for (auto& [field_name, field_mappingz] : class_mappingz.m_field_mappings) {
				class_mappingz.m_field_mappings[field_name].m_signature = replace_placeholders(field_mappingz.m_signature);
			}

			for (auto& [method_name, method_mappingz] : class_mappingz.m_method_mappings) {
				class_mappingz.m_method_mappings[method_name].m_signature = replace_placeholders(method_mappingz.m_signature);
			}
		}
	}
}