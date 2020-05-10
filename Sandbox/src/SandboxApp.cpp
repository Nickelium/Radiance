#include <Radiance.h>
#include <Radiance/EntryPoint.h>


static void ImGuiShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

}

class ExampleLayer : public Radiance::Layer
{
	Radiance::FrameBuffer* m_FrameBuffer;

	Radiance::PerspectiveController m_CameraController;

	Radiance::DataTime m_Time;

	ImGuiTextFilter m_Filter;

	std::vector<Radiance::ProfileResult> m_ProfileResults;
	std::vector<Radiance::ProfileResult> m_ProfileDisplayResults;

public:
	void DrawLog(const char* title, bool* p_opened = NULL)
	{
		ImGui::Begin(title, p_opened);
		if (ImGui::Button("Clear")) IMGUILOGGER->Clear();
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		m_Filter.Draw("Filter", -100.0f);
		ImGui::Separator();
		ImGui::BeginChild("scrolling");
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));

		if (copy) ImGui::LogToClipboard();

		ImVec4 col(0, 1, 1, 1);
		if (m_Filter.IsActive())
		{
			const char* buf_begin = IMGUILOGGER->GetBuffer().begin();
			const char* line = buf_begin;
			for (int line_no = 0; line != NULL; line_no++)
			{
				const char* line_end = (line_no < IMGUILOGGER->GetLineIndices().size()) ? buf_begin + IMGUILOGGER->GetLineIndices()[line_no] : NULL;
				if (m_Filter.PassFilter(line, line_end))
				{
					ImGui::TextColorUnformatted(col, line, line_end);
				}

				line = line_end && line_end[1] ? line_end + 1 : NULL;
			}
		}
		else
			ImGui::TextColorUnformatted(col, IMGUILOGGER->GetBuffer().begin());

		ImGui::LogFinish();

		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::End();
	}

	ExampleLayer(Radiance::Application* _application)
		: Layer(_application, new Radiance::Scene), 
		m_CameraController(),
		m_Time()
	{
		using namespace Radiance;
		RenderDevice* renderDevice = Locator::Get<RenderDevice>();
		ResourceLibrary* resourceLib = Locator::Get<ResourceLibrary>();
		
		m_FrameBuffer = renderDevice->CreateFrameBuffer(1, 1);
		
		Shader* shader = resourceLib->LoadShader("Basic1",
			"res/shaders/Basic.vs", "res/shaders/Basic.fs");

		Material* material1 = new Material(shader);

		MeshRender* meshRender = new MeshRender(CreateSphere({20.0f, 64, 64}), material1);
		//MeshRender* meshRender = new MeshRender(resourceLib->LoadMesh("CerberusMesh", "res/meshes/cerberus.fbx"), material1);
		Actor* actor = new Actor("Cerberus");

		actor->GetComponent<TransformComponent>()->m_Transform.position
			= glm::vec3(-40.0f, 0.0f, -100.0f);
		actor->GetComponent<TransformComponent>()->m_Transform.rotation
			= glm::vec3(-90.0f, 0.0f, 90.0f);
		actor->AddComponent(new MeshComponent(actor, meshRender));
		m_Scene->Add(actor);
		Texture2D* albedo = resourceLib->LoadTexture2D("Cerberus_Albedo", "res/textures/user.png");
		material1->SetUniform("u_Albedo", albedo, 0);

		m_CameraController.SetPosition({ 0.0f, 0.0f, 0.0f});

		Locator::Get<DeviceContext>()->SetClearColor({ 192 / 255.0f, 216 / 255.0f, 235 / 255.0f, 1.0f });
	}

	virtual ~ExampleLayer()
	{
		delete m_FrameBuffer;
	}

	virtual void Update(Radiance::DataTime _time)
	{
		using namespace Radiance;
		CPUPROFILE_SCOPE(Update);
		m_Time = _time;
		m_CameraController.Update(_time);
	}

	virtual void Render() override
	{
		using namespace Radiance;

		CPUPROFILE_SCOPE(Render);

		if (!m_Scene)
			return;
		m_FrameBuffer->Bind();
		
		{
			CPUPROFILE_BEGIN(RenderFrame);
			GPUPROFILE_BEGIN(RenderFrameGPU);
			Renderer::Begin(m_CameraController.GetCamera());
			{
				Locator::Get<DeviceContext>()->Clear();

				for (auto actor : m_Scene->GetActors())
				{
					auto meshComp = actor->GetComponent<MeshComponent>();
					if (meshComp)
					{
						TransformComponent* transformComp = actor->GetComponent<TransformComponent>();
						Renderer::Submit(meshComp->GetMesh(), transformComp->GetMatrix());
					}
				}
			}
			GPUPROFILE_END(RenderFrameGPU);
			CPUPROFILE_END(RenderFrame);
		}
		
		Renderer::End();
		m_FrameBuffer->UnBind();
	}

	virtual void RenderGUI() override
	{
		using namespace Radiance;

		CPUPROFILE_SCOPE(RenderUI);
	
		static bool p_open = true;

		int ImGuiDockNodeFlags_PassthruDockspace = 0;

		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		// Editor Panel ------------------------------------------------------------------------------
		//ImGui Displays reversed order
		ImGui::Begin("GPU Manufacturer Info");
		{
			/*auto apiData = RenderContext::GetAPI().data;
			ImGui::Text("Vendor: %s", apiData.vendor.c_str());
			ImGui::Text("Renderer: %s", apiData.renderer.c_str());
			ImGui::Text("Version: %s", apiData.version.c_str());*/
			static float currentTime;
			static float currentFps;
			if (abs(currentTime - m_Time.total) > 1.0f)
			{
				currentTime = m_Time.total;
				currentFps = 1.0f / m_Time.dt;
			}
			ImGui::Text("Performance: %.1f fps", currentFps);
		}
		ImGui::End();

		DrawLog("Engine Logger");

		ImGui::Begin("Properties");
		{
			ImGui::Columns(2);

			bool b;
			ImGui::Property("Test ImGui::Property", b);

			ImGui::Columns();
		}
		ImGui::End();

		ImGui::Begin("Scene##");
		{
			////////// ACTORS
			if (ImGui::TreeNodeEx("Actors##", ImGuiTreeNodeFlags_DefaultOpen))
			{
				int i = 0;
				for (Actor* actor : m_Scene->GetActors())
				{
					if (ImGui::TreeNodeEx(
						(actor->GetName() + "##" + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
					{
						TransformComponent* comp = actor->GetComponent<TransformComponent>();

						if (ImGui::TreeNodeEx(
							(comp->GetName() + "##" + std::to_string(i)).c_str(), ImGuiTreeNodeFlags_DefaultOpen))
						{
							Transform& trans = comp->m_Transform;

							ImGui::Columns(2);
						
							ImGui::Property("Position", trans.position, -50, 50);
							ImGui::Property("Rotation", trans.rotation, -180, 180);
							ImGui::Property("Scale", trans.scale, -1, 1);

							ImGui::Columns();
							ImGui::TreePop();
						}
						ImGui::TreePop();
					}
					++i;

				}
				ImGui::TreePop();
			}
			ImGui::Separator();

			/////// CAMERA
			if(ImGui::TreeNodeEx("Camera##", ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Columns(2);
				glm::vec3 pos = m_CameraController.GetPosition();
				if (ImGui::Property("Position", pos, -50, 50))
					m_CameraController.SetPosition(pos);
				glm::vec2 rot = m_CameraController.GetRotation();
				if (ImGui::Property("Theta/Phi", rot, -180, 180))
					m_CameraController.SetRotation(rot);
				ImGui::Columns();

				ImGui::TreePop();
			}
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		auto viewportSize = ImGui::GetContentRegionAvail();
		m_CameraController.SetAspectRatio(viewportSize.x / viewportSize.y);
		m_FrameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		ImGui::Image((void*)(uintptr_t)m_FrameBuffer->GetRTBuffer()->GetHandle(), viewportSize, { 0, 1 }, { 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Docking"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Flag: NoSplit", "", (opt_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 opt_flags ^= ImGuiDockNodeFlags_NoSplit;
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (opt_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  opt_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				if (ImGui::MenuItem("Flag: NoResize", "", (opt_flags & ImGuiDockNodeFlags_NoResize) != 0))                opt_flags ^= ImGuiDockNodeFlags_NoResize;
				if (ImGui::MenuItem("Flag: PassthruDockspace", "", (opt_flags & ImGuiDockNodeFlags_PassthruDockspace) != 0))       opt_flags ^= ImGuiDockNodeFlags_PassthruDockspace;
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (opt_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          opt_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				ImGui::Separator();
				if (ImGui::MenuItem("Close DockSpace", NULL, false, p_open != NULL))
					p_open = false;
				ImGui::EndMenu();
			}
			ImGuiShowHelpMarker("Help Marker");
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Profiling");
		static float currentTotalTime = 0.0f;
		if (abs(currentTotalTime - m_Time.total) > 1.0f)
		{
			currentTotalTime = m_Time.total;
			m_ProfileDisplayResults = m_ProfileResults;
		}
		for (auto& result : m_ProfileDisplayResults)
		{
			char label[50];
			strcpy_s(label, "%.3f ms ");
			strcat_s(label, result.name);
			ImGui::Text(label, result.time * 1e3f);
		}
		m_ProfileResults.clear();
		ImGui::End();

		ImGui::End();

	}

	void OnEvent(Radiance::Event& event) override
	{
		if (event.GetEventType() == Radiance::EventType::KeyPressed)
		{
			/*Radiance::KeyPressedEvent& e = (Radiance::KeyPressedEvent&)event;*/
		
		}
	}

};

class SandboxApplication : public Radiance::Application
{
public:
	SandboxApplication()
		: Application("Radiance Engine", 1600, 900)
	{
		using namespace Radiance;
		RAD_INFO("Creating Sandbox Application");
		PushLayer(new ExampleLayer(this));
		//GetWindow()->SetVSync(false);
	}

	virtual ~SandboxApplication()
	{
		RAD_INFO("Destroying Sandbox Application");
	}

	virtual void OnEvent(Radiance::Event& _event)
	{
		using namespace Radiance;
		if (_event.GetEventType() == Radiance::EventType::KeyReleased)
		{
			KeyReleasedEvent& relEvent = (KeyReleasedEvent&)_event;
			if (relEvent.GetKeyCode() == RAD_KEY_ESCAPE)
				Application::CloseWindow();
		}
	}
private:
};

class WindowApplication : public Radiance::Application
{
public:
	WindowApplication()
		: Application("Radiance Engine", 1600, 900)
	{
		using namespace Radiance;
		RAD_INFO("Creating Window Application");
		//PushLayer(new ExampleLayer(this));
		//GetWindow()->SetVSync(false);
	}

	virtual ~WindowApplication()
	{
		RAD_INFO("Destroying Window Application");
	}

	virtual void OnEvent(Radiance::Event& _event)
	{
		using namespace Radiance;
		if (_event.GetEventType() == Radiance::EventType::KeyReleased)
		{
			KeyReleasedEvent& relEvent = (KeyReleasedEvent&)_event;
			if (relEvent.GetKeyCode() == RAD_KEY_ESCAPE)
				Application::CloseWindow();
		}
	}
private:
};

Radiance::Application* CreateApplication()
{
	// First set API before calling anything
	Radiance::API = Radiance::RenderAPI::DX11;

	//return new SandboxApplication;
	return new WindowApplication;
}