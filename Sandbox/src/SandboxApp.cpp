#include <Radiance.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi


class ExampleLayer : public Radiance::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnUpdate()
	{
		//RAD_TRACE("{0}", "ExampleLayer : Update");
		if (Radiance::Input::IsKeyPressed(RAD_KEY_A))
			RAD_INFO("KEy A is pressed : {0}", RAD_KEY_A);
	}

	virtual void OnEvent(Radiance::Event& _event)
	{
		//RAD_TRACE("{0}", _event);
	}
};

class SandboxApplication : public Radiance::Application
{
public:
	SandboxApplication()
	{
		RAD_INFO("Creating Sandbox Application");
		PushLayer(new ExampleLayer);
		PushOverlay(new Radiance::ImGuiLayer(*this));
	}

	virtual ~SandboxApplication()
	{
		RAD_INFO("Destroying Sandbox Application");
	}
};


Radiance::Application* CreateApplication()
{
	return new SandboxApplication;
}