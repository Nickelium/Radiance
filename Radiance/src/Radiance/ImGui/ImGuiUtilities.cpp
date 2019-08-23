#include "pch.h"
#include "ImGuiUtilities.h"

#include <glm/gtc/type_ptr.hpp>

namespace ImGui
{
	void TextColorUnformatted(const ImVec4& _color, const char* _text, const char* _text_end)
	{
		PushStyleColor(ImGuiCol_Text, _color);
		TextUnformatted(_text, _text_end);
		PopStyleColor();
	}

	void Property(const std::string& name, bool& value)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		ImGui::Checkbox(id.c_str(), &value);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void Property(const std::string& name, float& value, float min, float max, PropertyFlag /*flags*/)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		ImGui::SliderFloat(id.c_str(), &value, min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void Property(const std::string& name, glm::vec2& value, float min, float max, PropertyFlag /*flags*/)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		ImGui::SliderFloat2(id.c_str(), glm::value_ptr(value), min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void Property(const std::string& name, glm::vec3& value, float min, float max, PropertyFlag flags)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ImGui::ColorEdit3(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ImGui::SliderFloat3(id.c_str(), glm::value_ptr(value), min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void Property(const std::string& name, glm::vec4& value, float min, float max, PropertyFlag flags)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ImGui::ColorEdit4(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ImGui::SliderFloat4(id.c_str(), glm::value_ptr(value), min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}
}