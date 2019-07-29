#include <Radiance.h>
#include <glm/gtc/type_ptr.hpp>


#include <GLFW/glfw3.h>


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

	Radiance::Actor* m_Actor1;
	Radiance::Actor* m_Actor2;

	Radiance::MeshRender* m_MeshRender1;
	Radiance::MeshRender* m_MeshRender2;

	Radiance::Texture2D* m_Texture;

	Radiance::Camera* m_Camera;

	Radiance::DataTime m_Time;
public:

	enum class PropertyFlag
	{
		None = 0, ColorProperty = 1
	};

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

	void Property(const std::string& name, float& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		ImGui::SliderFloat(id.c_str(), &value, min, max);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void Property(const std::string& name, glm::vec3& value, PropertyFlag flags)
	{
		Property(name, value, -1.0f, 1.0f, flags);
	}

	void Property(const std::string& name, glm::vec3& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ImGui::ColorEdit3(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ImGui::SliderFloat3(id.c_str(), glm::value_ptr(value), min, max);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}

	void Property(const std::string& name, glm::vec4& value, PropertyFlag flags)
	{
		Property(name, value, -1.0f, 1.0f, flags);
	}

	void Property(const std::string& name, glm::vec4& value, float min = -1.0f, float max = 1.0f, PropertyFlag flags = PropertyFlag::None)
	{
		ImGui::Text(name.c_str());
		ImGui::NextColumn();
		ImGui::PushItemWidth(-1);

		std::string id = "##" + name;
		if ((int)flags & (int)PropertyFlag::ColorProperty)
			ImGui::ColorEdit4(id.c_str(), glm::value_ptr(value), ImGuiColorEditFlags_NoInputs);
		else
			ImGui::SliderFloat4(id.c_str(), glm::value_ptr(value), min, max);

		ImGui::PopItemWidth();
		ImGui::NextColumn();
	}


	ExampleLayer(Radiance::Application* _application)
		: Layer(_application, new Radiance::Scene), 
		m_Camera(new Radiance::FreeCamera),
		m_Time()
	{
		using namespace Radiance;
		RenderDevice* renderDevice = Locator::Get<RenderDevice>();

		m_FrameBuffer = renderDevice->CreateFrameBuffer(1000, 1000);

		std::string vertexShader = ReadFile("res/shaders/Basic.vs");
		std::string fragmentShader = ReadFile("res/shaders/Basic.fs");
		Shader* shader1 = renderDevice->CreateShader(vertexShader, fragmentShader);

		m_MeshRender1 = new MeshRender(CreateTriangle(), shader1);
		m_Actor1 = new Actor();
		m_Actor1->GetComponent<TransformComponent>()->m_Transform.position 
			= glm::vec3(-4.0f, 0.0f, -10.0f);
		m_Actor1->AddComponent(new MeshComponent(m_Actor1, m_MeshRender1));
		m_Scene->Add(m_Actor1);
		
		std::string vertexShader2 = ReadFile("res/shaders/Basic2.vs");
		std::string fragmentShader2 = ReadFile("res/shaders/Basic2.fs");
		Shader* shader2 = renderDevice->CreateShader(vertexShader2, fragmentShader2);

		m_MeshRender2 = new MeshRender(CreateCube(), shader2);
		m_Actor2 = new Actor();
		m_Actor2->GetComponent<TransformComponent>()->m_Transform.position
			= glm::vec3(4.0f, 0.0f, -10.0f);
		m_Actor2->AddComponent(new MeshComponent(m_Actor2, m_MeshRender2));
		m_Scene->Add(m_Actor2);

		m_Texture = renderDevice->CreateTexture2D("res/textures/user.png");
	}

	virtual ~ExampleLayer()
	{
		delete m_Texture;
		delete m_Camera;
	}

	virtual void Update(Radiance::DataTime _time)
	{
		using namespace Radiance;
		m_Time = _time;
		m_Camera->Update(_time);
	}

	virtual void Render() override
	{
		using namespace Radiance;

		RenderCommand::SetClearColor({ 1.0f, 1.0f, 0.0f, 1.0f });

		if (!m_Scene)
			return;

		m_FrameBuffer->Bind();
		Renderer::Begin(*m_Camera);
		{
			RenderCommand::Clear();
			int i = 0;
			for (auto actor : m_Scene->GetActors())
			{
				auto meshComp = actor->GetComponent<MeshComponent>();
				if (meshComp)
				{
					int slot = 0;
					if (i == 1)
					{
						m_Texture->Bind(slot);
						meshComp->GetMesh()->GetShader()->SetUniform("u_Texture", slot);
					}
					TransformComponent* transformComp = actor->GetComponent<TransformComponent>();
					Renderer::Submit(meshComp->GetMesh(), transformComp->GetMatrix());
				}
				++i;
			}
		}
		Renderer::End();
		m_FrameBuffer->UnBind();
	}

	virtual void RenderGUI() override
	{
		/*using namespace Radiance;
		ImGui::Begin("FPS");
		std::string fps = std::to_string(1.0f / m_Time.dt);
		ImGui::Text(fps.c_str());
		ImGui::End();

		ImGui::Begin("Test");
		ImGui::Text("Camera Transform");
		ImGui::SliderFloat3("Camera Position", &m_Camera->position.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Camera Rotation", &m_Camera->rotation.x , -90.0f, 90.0f);

		int i = 0;
		ImGui::Text("Scene Objects");
		for (Actor* actor : m_Scene->GetActors())
		{
			TransformComponent* comp = actor->GetComponent<TransformComponent>();
			Transform& trans = comp->m_Transform;
			ImGui::SliderFloat3(std::string("Pos " + std::to_string(i)).c_str(), 
				&trans.position.x, -10.0f, 10.0f);
			ImGui::SliderFloat3(std::string("Rot " + std::to_string(i)).c_str(), 
				&trans.rotation.x, -180, 180);
			ImGui::SliderFloat3(std::string("Scale " + std::to_string(i)).c_str(), 
				&trans.scale.x, -10.0f, 10.0f);
			++i;
		}
		ImGui::End();*/

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
		ImGui::Begin("Model");
		int i;
		ImGui::RadioButton("Spheres", &i, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Model", &i, 1);

		ImGui::Begin("Environment");

		ImGui::Columns(2);
		ImGui::AlignTextToFramePadding();

		glm::vec3 v3;
		float f;
		bool b;
		Property("Light Direction", v3);
		Property("Light Radiance", v3, PropertyFlag::ColorProperty);
		Property("Light Multiplier", f, 0.0f, 5.0f);
		Property("Exposure", f, 0.0f, 5.0f);

		Property("Radiance Prefiltering", b);
		Property("Env Map Rotation", f, -360.0f, 360.0f);

		ImGui::Columns(1);

		ImGui::End();

		ImGui::Separator();
		{
			ImGui::Text("Mesh");
			std::string fullpath = "None";
			ImGui::Text(fullpath.c_str());
			ImGui::SameLine();
			if (ImGui::Button("...##Mesh"))
			{
			}
		}
		ImGui::Separator();

		// Textures ------------------------------------------------------------------------------
		{
			// Albedo
			if (ImGui::CollapsingHeader("Albedo", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
				
				}
				ImGui::SameLine();
				ImGui::BeginGroup();
				ImGui::Checkbox("Use##AlbedoMap", &b);
				if (ImGui::Checkbox("sRGB##AlbedoMap", &b))
				{
					
				}
				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::ColorEdit3("Color##Albedo", glm::value_ptr(v3), ImGuiColorEditFlags_NoInputs);
			}
		}
		{
			// Normals
			if (ImGui::CollapsingHeader("Normals", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
				}
				ImGui::SameLine();
				ImGui::Checkbox("Use##NormalMap", &b);
			}
		}
		{
			// Metalness
			if (ImGui::CollapsingHeader("Metalness", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
				}
				ImGui::SameLine();
				ImGui::Checkbox("Use##MetalnessMap", &b);
				ImGui::SameLine();
				ImGui::SliderFloat("Value##MetalnessInput", &f, 0.0f, 1.0f);
			}
		}
		{
			// Roughness
			if (ImGui::CollapsingHeader("Roughness", nullptr, ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
				ImGui::PopStyleVar();
				if (ImGui::IsItemHovered())
				{
				}
				ImGui::SameLine();
				ImGui::Checkbox("Use##RoughnessMap", &b);
				ImGui::SameLine();
				ImGui::SliderFloat("Value##RoughnessInput", &f, 0.0f, 1.0f);
			}
		}

		ImGui::Separator();

		if (ImGui::TreeNode("Shaders"))
		{
			ImGui::TreePop();
		}


		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		auto viewportSize = ImGui::GetContentRegionAvail();
		m_FrameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);
		ImGui::Image((void*)m_FrameBuffer->GetColorAttachment()->GetHandle(), viewportSize, { 0, 1 }, { 1, 0 });
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
			ImGuiShowHelpMarker(
				"You can _always_ dock _any_ window into another by holding the SHIFT key while moving a window. Try it now!" "\n"
				"This demo app has nothing to do with it!" "\n\n"
				"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
				"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
				"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)"
			);

			ImGui::EndMenuBar();
		}

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
	{
		using namespace Radiance;
		RAD_INFO("Creating Sandbox Application");
		PushLayer(new ExampleLayer(this));
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

Radiance::Application* CreateApplication()
{
	return new SandboxApplication;
}