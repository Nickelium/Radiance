#pragma once

namespace ImGui
{
	void TextColorUnformatted(const ImVec4& _color, const char* _text, const char* _text_end = nullptr);

	enum class PropertyFlag
	{
		None = 0, ColorProperty = 1
	};

	void Property(const std::string& name, bool& value);

	void Property(const std::string& name, float& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);

	void Property(const std::string& name, glm::vec2& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);

	void Property(const std::string& name, glm::vec3& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);

	void Property(const std::string& name, glm::vec4& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None);

}
