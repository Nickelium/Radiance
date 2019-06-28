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
	ExampleLayer(Radiance::Application* _application)
		: Layer(_application, "Example")
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
	Radiance::VertexArray* m_VertexArray2;
	Radiance::Shader* m_Shader;
	Radiance::Shader* m_Shader2;


	SandboxApplication()
	{
		using namespace Radiance;
		RAD_INFO("Creating Sandbox Application");
		PushLayer(new ExampleLayer(this));

		m_VertexArray = m_RenderDevice->CreateVertexArray();

		std::vector<float> vertices =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			+0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, +0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};
		VertexBuffer* vertexBuffer = m_RenderDevice->CreateVertexBuffer(vertices);
		BufferLayout layout =
		{
			{DataType::Float3, "a_Position"},
			{DataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		std::vector<unsigned int> indices =
		{
			0, 1, 2
		};
		IndexBuffer* indexBuffer = m_RenderDevice->CreateIndexBuffer(indices);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_VertexArray2 = m_RenderDevice->CreateVertexArray();
		std::vector<float> vertices2 =
		{
			-0.75f, -0.75f, +0.75f,
			+0.75f, -0.75f, +0.75f,
			+0.75f, +0.75f, +0.75f, 
			-0.75f, +0.75f, +0.75f
		};
		vertexBuffer = m_RenderDevice->CreateVertexBuffer(vertices2);
		vertexBuffer->SetLayout
		({
			{DataType::Float3,"a_Pos"}
		});
		m_VertexArray2->AddVertexBuffer(vertexBuffer);

		std::vector<uint32_t> indices2 =
		{
			0, 1, 2,
			2, 3, 0
		};
		indexBuffer = m_RenderDevice->CreateIndexBuffer(indices2);
		m_VertexArray2->SetIndexBuffer(indexBuffer);

		std::string vertexShader = ReadFile("res/shaders/Basic.vs");
		std::string fragmentShader = ReadFile("res/shaders/Basic.fs");
		m_Shader = m_RenderDevice->CreateShader(vertexShader, fragmentShader);

		std::string vertexShader2 = ReadFile("res/shaders/Basic2.vs");
		std::string fragmentShader2 = ReadFile("res/shaders/Basic2.fs");
			
		m_Shader2 = m_RenderDevice->CreateShader(vertexShader2, fragmentShader2);
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

			m_Shader2->Bind();
			Renderer::Submit(m_VertexArray2);
			m_Shader2->UnBind();
		}
		Renderer::End();
	}

	virtual void OnEvent(Radiance::Event& _event)
	{
		using namespace Radiance;
		EventDispatcher dispatcher(_event);
		//dispatcher.Dispatch<KeyReleasedEvent>(BIND_FN(Application::OnWindowClose));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_FN(Application::OnWindowClose));
	}

	virtual ~SandboxApplication()
	{
		delete m_VertexArray;
		delete m_Shader;

		delete m_VertexArray2;
		delete m_Shader2;
		RAD_INFO("Destroying Sandbox Application");
	}
private:
};


Radiance::Application* CreateApplication()
{
	return new SandboxApplication;
}