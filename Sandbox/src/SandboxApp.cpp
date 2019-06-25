#include <Radiance.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include <imgui.h>
#include <GLFW/glfw3.h>

class ExampleLayer : public Radiance::Layer
{
private:
	struct ExampleAppLog
	{
		ImGuiTextBuffer     Buf;
		ImGuiTextFilter     Filter;
		ImVector<int>       LineOffsets;        // Index to lines offset. We maintain this with AddLog() calls, allowing us to have a random access on lines
		bool                AutoScroll;
		bool                ScrollToBottom;

		ExampleAppLog()
		{
			AutoScroll = true;
			ScrollToBottom = false;
			Clear();
		}

		void    Clear()
		{
			Buf.clear();
			LineOffsets.clear();
			LineOffsets.push_back(0);
		}

		void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
		{
			int old_size = Buf.size();
			va_list args;
			va_start(args, fmt);
			Buf.appendfv(fmt, args);
			va_end(args);
			for (int new_size = Buf.size(); old_size < new_size; old_size++)
				if (Buf[old_size] == '\n')
					LineOffsets.push_back(old_size + 1);
			if (AutoScroll)
				ScrollToBottom = true;
		}

		void    Draw(const char* title, bool* p_open = NULL)
		{
			if (!ImGui::Begin(title, p_open))
			{
				ImGui::End();
				return;
			}

			// Options menu
			if (ImGui::BeginPopup("Options"))
			{
				if (ImGui::Checkbox("Auto-scroll", &AutoScroll))
					if (AutoScroll)
						ScrollToBottom = true;
				ImGui::EndPopup();
			}

			// Main window
			if (ImGui::Button("Options"))
				ImGui::OpenPopup("Options");
			ImGui::SameLine();
			bool clear = ImGui::Button("Clear");
			ImGui::SameLine();
			bool copy = ImGui::Button("Copy");
			ImGui::SameLine();
			Filter.Draw("Filter", -100.0f);

			ImGui::Separator();
			ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

			if (clear)
				Clear();
			if (copy)
				ImGui::LogToClipboard();

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
			const char* buf = Buf.begin();
			const char* buf_end = Buf.end();
			if (Filter.IsActive())
			{
				// In this example we don't use the clipper when Filter is enabled.
				// This is because we don't have a random access on the result on our filter.
				// A real application processing logs with ten of thousands of entries may want to store the result of search/filter.
				// especially if the filtering function is not trivial (e.g. reg-exp).
				for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					if (Filter.PassFilter(line_start, line_end))
						ImGui::TextUnformatted(line_start, line_end);
				}
			}
			else
			{
				// The simplest and easy way to display the entire buffer:
				//   ImGui::TextUnformatted(buf_begin, buf_end);
				// And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward to skip non-visible lines.
				// Here we instead demonstrate using the clipper to only process lines that are within the visible area.
				// If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them on your side is recommended.
				// Using ImGuiListClipper requires A) random access into your data, and B) items all being the  same height,
				// both of which we can handle since we an array pointing to the beginning of each line of text.
				// When using the filter (in the block of code above) we don't have random access into the data to display anymore, which is why we don't use the clipper.
				// Storing or skimming through the search result would make it possible (and would be recommended if you want to search through tens of thousands of entries)
				ImGuiListClipper clipper;
				clipper.Begin(LineOffsets.Size);
				while (clipper.Step())
				{
					for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
					{
						const char* line_start = buf + LineOffsets[line_no];
						const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
						ImGui::TextUnformatted(line_start, line_end);
					}
				}
				clipper.End();
			}
			ImGui::PopStyleVar();

			if (ScrollToBottom)
				ImGui::SetScrollHereY(1.0f);
			ScrollToBottom = false;
			ImGui::EndChild();
			ImGui::End();
		}
	};

public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnUpdate() override
	{
		//RAD_TRACE("{0}", "ExampleLayer : Update");
		if (Radiance::Input::IsKeyPressed(RAD_KEY_A))
			RAD_INFO("KEy A is pressed : {0}", RAD_KEY_A);
	}

	virtual void OnEvent(Radiance::Event& _event) override
	{
		//RAD_TRACE("{0}", _event);
	}

	virtual void OnImGuiRender() override
	{
		static bool open = true;
		bool* p_open = &open;
		static ExampleAppLog log;

		// For the demo: add a debug button _BEFORE_ the normal log window contents
		// We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
		// Most of the contents of the window will be added by the log.Draw() call.
		ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
		ImGui::Begin("Example: Log", p_open);
		static float timePrev = 0.0f;
		static float time = 0.0f;
		time = (float)glfwGetTime();
		float fps = 1.0f / (time - timePrev);
		timePrev = time;
		if (ImGui::SmallButton(std::string("[Debug] Add 5 entries : FPS " + std::to_string(fps)).c_str()))
		{
			static int counter = 0;
			for (int n = 0; n < 5; n++)
			{
				const char* categories[3] = { "info", "warn", "error" };
				const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
				log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
					ImGui::GetFrameCount(), categories[counter % IM_ARRAYSIZE(categories)], ImGui::GetTime(), words[counter % IM_ARRAYSIZE(words)]);
				counter++;
			}
		}
		ImGui::End();

		// Actually call in the regular Log helper (which will Begin() into the same window as we just did)
		
		log.Draw("Example: Log", p_open);
	}
};

class SandboxApplication : public Radiance::Application
{
public:

	Radiance::VertexArray* m_VertexArray;
	Radiance::Shader* m_Shader;

	SandboxApplication()
	{
		using namespace Radiance;
		RAD_INFO("Creating Sandbox Application");
		PushLayer(new ExampleLayer);

		m_VertexArray = m_RenderDevice->CreateVertexArray();

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			+0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, +0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};
		VertexBuffer* vertexBuffer = m_RenderDevice->CreateVertexBuffer(vertices, sizeof(vertices));
		BufferLayout layout =
		{
			{DataType::Float3, "a_Position"},
			{DataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] =
		{
			0, 1, 2
		};
		IndexBuffer* indexBuffer = m_RenderDevice->CreateIndexBuffer(indices, 3);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexShader =
			R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
				
			out vec4 v_Color;
			out vec3 v_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0f);
				v_Color = a_Color;
				v_Position = a_Position;
			}
		)";

		std::string fragmentShader =
			R"(
			#version 330 core
			
			in vec4 v_Color;
			in vec3 v_Position;

			layout(location = 0) out vec4 o_Color;

			void main()
			{
				o_Color = v_Color;
				//o_Color = vec4((v_Position * 0.5f + 0.5f).rg, 0.0f, 1.0f);
			}
		)";
		m_Shader = m_RenderDevice->CreateShader(vertexShader, fragmentShader);
	}

	virtual void Render()
	{
		using namespace Radiance;

		RenderCommand::SetClearColor({ 1.0f, 1.0f, 0.0f, 1.0f });
		RenderCommand::Clear();
		Renderer::Begin();
		{
			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);
			m_Shader->UnBind();
		}
		Renderer::End();
	}

	virtual ~SandboxApplication()
	{
		delete m_VertexArray;
		delete m_Shader;
		RAD_INFO("Destroying Sandbox Application");
	}
};


Radiance::Application* CreateApplication()
{
	return new SandboxApplication;
}