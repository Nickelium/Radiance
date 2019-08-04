#include "pch.h"
#include "ImGuiUtilities.h"

namespace ImGui
{
	void TextColorUnformatted(const ImVec4& _color, const char* _text, const char* _text_end)
	{
		PushStyleColor(ImGuiCol_Text, _color);
		TextUnformatted(_text, _text_end);
		PopStyleColor();
	}
}