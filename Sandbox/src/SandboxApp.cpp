#include <Radiance.h>

#include <GLFW/glfw3.h>

class ExampleLayer : public Radiance::Layer
{
	Radiance::Actor* m_Actor1;
	Radiance::Actor* m_Actor2;

	Radiance::Mesh* m_Mesh1;
	Radiance::Mesh* m_Mesh2;

	Radiance::Texture2D* m_Texture;

	Radiance::Orthographic m_Camera;
public:
	ExampleLayer(Radiance::Application* _application)
		: Layer(_application, new Radiance::Scene), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)
	{
		using namespace Radiance;
		RenderDevice* renderDevice = m_Application->GetRenderDevice();

		VertexArray* vertexArray1 = renderDevice->CreateVertexArray();

		std::vector<float> vertices =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			+0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.0f, +0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};
		VertexBuffer* vertexBuffer = renderDevice->CreateVertexBuffer(vertices);
		BufferLayout layout =
		{
			{DataType::Float3, "a_Position"},
			{DataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		vertexArray1->AddVertexBuffer(vertexBuffer);

		std::vector<unsigned int> indices =
		{
			0, 1, 2
		};
		IndexBuffer* indexBuffer = renderDevice->CreateIndexBuffer(indices);
		vertexArray1->SetIndexBuffer(indexBuffer);

		VertexArray* vertexArray2 = renderDevice->CreateVertexArray();
		std::vector<float> vertices2 =
		{
			-0.75f, -0.75f, -0.75f, 0.0f, 0.0f,
			+0.75f, -0.75f, -0.75f, 1.0f, 0.0f,
			+0.75f, +0.75f, -0.75f, 1.0f, 1.0f,
			-0.75f, +0.75f, -0.75f, 0.0f, 1.0f
		};
		vertexBuffer = renderDevice->CreateVertexBuffer(vertices2);
		vertexBuffer->SetLayout
		({
			{DataType::Float3,"a_Pos"},
			{DataType::Float2, "a_Tex"}
		});
		vertexArray2->AddVertexBuffer(vertexBuffer);

		std::vector<uint32_t> indices2 =
		{
			0, 1, 2,
			2, 3, 0
		};
		indexBuffer = renderDevice->CreateIndexBuffer(indices2);
		vertexArray2->SetIndexBuffer(indexBuffer);

		std::string vertexShader = ReadFile("res/shaders/Basic.vs");
		std::string fragmentShader = ReadFile("res/shaders/Basic.fs");
		Shader* shader1 = renderDevice->CreateShader(vertexShader, fragmentShader);

		m_Mesh1 = new Mesh(vertexArray1, shader1);
		m_Actor1 = new Actor();
		m_Actor1->AddComponent(new MeshComponent(m_Actor1, m_Mesh1));
		m_Scene->Add(m_Actor1);
		
		std::string vertexShader2 = ReadFile("res/shaders/Basic2.vs");
		std::string fragmentShader2 = ReadFile("res/shaders/Basic2.fs");

		Shader* shader2 = renderDevice->CreateShader(vertexShader2, fragmentShader2);

		shader2->SetUniformFloat("u_Float", 0.5f);

		m_Mesh2 = new Mesh(vertexArray2, shader2);
		m_Actor2 = new Actor();
		m_Actor2->AddComponent(new MeshComponent(m_Actor2, m_Mesh2));
		m_Scene->Add(m_Actor2);

		m_Texture = renderDevice->CreateTexture2D("res/textures/user.png");
	}

	virtual ~ExampleLayer()
	{
		delete m_Texture;
	}

	virtual void Render() override
	{
		using namespace Radiance;

		RenderCommand::SetClearColor({ 1.0f, 1.0f, 0.0f, 1.0f });

		if (!m_Scene)
			return;

		Renderer::Begin(m_Camera);
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
	
					Renderer::Submit(meshComp->GetMesh());
				}
				++i;
			}
		}
		Renderer::End();
	}

	virtual void RenderGUI() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		glm::vec3 camPos = m_Camera.GetPosition();
		ImGui::SliderFloat3("Camera Position", &camPos[0], -1.0f, 1.0f);
		m_Camera.SetPosition(camPos);
		glm::vec3 camRot = m_Camera.GetRotations();
		ImGui::SliderFloat3("Camera Rotation", &camRot[0], -180.0f, 180.0f);
		m_Camera.SetRotations(camRot);
		ImGui::End();
	}

	void OnEvent(Radiance::Event& event) override
	{
		if (event.GetEventType() == Radiance::EventType::KeyPressed)
		{
			Radiance::KeyPressedEvent& e = (Radiance::KeyPressedEvent&)event;
			if (e.GetKeyCode() == RAD_KEY_TAB)
				RAD_TRACE("Tab key is pressed (event)!");
			RAD_TRACE("{0}", (char)e.GetKeyCode());
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