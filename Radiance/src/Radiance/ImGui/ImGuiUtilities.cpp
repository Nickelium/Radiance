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

	bool Property(const std::string& name, bool& value)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		bool ret = ImGui::Checkbox(id.c_str(), &value);

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return ret;
	}

	bool Property(const std::string& name, float& value, float min, float max, PropertyFlag /*flags*/)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		bool ret = ImGui::SliderFloat(id.c_str(), &value, min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return ret;
	}

	bool Property(const std::string& name, glm::vec2& value, float min, float max, PropertyFlag /*flags*/)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		bool ret = ImGui::SliderFloat2(id.c_str(), glm::value_ptr(value), min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return ret;
	}

	bool Property(const std::string& name, glm::vec3& value, float min, float max, PropertyFlag flags)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		bool ret;
		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ret = ImGui::ColorEdit3(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ret = ImGui::SliderFloat3(id.c_str(), glm::value_ptr(value), min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return ret;
	}

	bool Property(const std::string& name, glm::vec4& value, float min, float max, PropertyFlag flags)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		bool ret;
		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ret = ImGui::ColorEdit4(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ret = ImGui::SliderFloat4(id.c_str(), glm::value_ptr(value), min, max, "%.2f");

		ImGui::PopItemWidth();
		ImGui::NextColumn();

		return ret;
	}
}