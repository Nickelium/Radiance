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
public:
	ExampleLayer(Radiance::Application* _application)
		: Layer(_application, new Radiance::Scene), 
		m_Camera(new Radiance::FreeCamera)
	{
		using namespace Radiance;
		RenderDevice* renderDevice = m_Application->GetRenderDevice();

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