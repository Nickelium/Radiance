#include <Radiance.h>

#include <GLFW/glfw3.h>

class ExampleLayer : public Radiance::Layer
{
	Radiance::Actor* m_Actor1;
	Radiance::Actor* m_Actor2;

	Radiance::MeshRender* m_MeshRender1;
	Radiance::MeshRender* m_MeshRender2;

	Radiance::Texture2D* m_Texture;

	Radiance::Camera* m_Camera;

	Radiance::DataTime m_Time;
public:
	ExampleLayer(Radiance::Application* _application)
		: Layer(_application, new Radiance::Scene), 
		m_Camera(new Radiance::FreeCamera)
	{
		using namespace Radiance;
		RenderDevice* renderDevice = Locator::Get<RenderDevice>();

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
						meshComp->GetMesh()->GetShader()->SetUniformInt("u_Texture", slot);
					}
					TransformComponent* transformComp = actor->GetComponent<TransformComponent>();
					Renderer::Submit(meshComp->GetMesh(), transformComp->GetMatrix());
				}
				++i;
			}
		}
		Renderer::End();
	}

	virtual void RenderGUI() override
	{
		using namespace Radiance;
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
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Viewport");
		auto viewportSize = ImGui::GetContentRegionAvail();
		ImGui::End();
		ImGui::PopStyleVar();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Docking"))
			{
				if (ImGui::MenuItem("Close DockSpace", NULL, false, NULL))
					;
				ImGui::EndMenu();
			}

			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);

				std::string str =
					"You can _always_ dock _any_ window into another by holding the SHIFT key while moving a window. Try it now!" "\n"
					"This demo app has nothing to do with it!" "\n\n"
					"This demo app only demonstrate the use of ImGui::DockSpace() which allows you to manually create a docking node _within_ another window. This is useful so you can decorate your main application window (e.g. with a menu bar)." "\n\n"
					"ImGui::DockSpace() comes with one hard constraint: it needs to be submitted _before_ any window which may be docked into it. Therefore, if you use a dock spot as the central point of your application, you'll probably want it to be part of the very first window you are submitting to imgui every frame." "\n\n"
					"(NB: because of this constraint, the implicit \"Debug\" window can not be docked into an explicit DockSpace() node, because that window is submitted as part of the NewFrame() call. An easy workaround is that you can create your own implicit \"Debug##2\" window after calling DockSpace() and leave it in the window stack for anyone to use.)";

				ImGui::TextUnformatted(str.c_str());
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}

			ImGui::EndMenuBar();
		}

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