#include "pch.h"
#include "ImGuiLayer.h"

#include <imgui.h>

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Radiance/Application.h"

//TEMPorary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Radiance
{
	ImGuiLayer::ImGuiLayer(Application& _application)
		: Layer("ImGuiLayer"),
		m_Application(_application)
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//TEMP
		// Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{

		ImGuiIO& io = ImGui::GetIO();
		Window* pWindow = m_Application.GetWindow();
		io.DisplaySize = ImVec2((float)pWindow->GetWidth(), (float)pWindow->GetHeight());
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? time - m_Time : 1.0f / 60.0f;
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& _event)
	{	
		EventDispatcher dispatcher(_event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(ImGuiLayer::OnWindowsResized));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[_event.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[_event.GetMouseButton()] = false;

		return false;	
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = {_event.GetX(), _event.GetY()};

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += _event.GetOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[_event.GetKeyCode()] = true;

		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[_event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (_event.GetKeyCode() > 0 && _event.GetKeyCode() < 0x10000)
			io.AddInputCharacter((unsigned int)_event.GetKeyCode());

		return false;
	}

	bool ImGuiLayer::OnWindowsResized(WindowResizeEvent& _event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = { (float)_event.GetWidth(), (float)_event.GetHeight() };
		io.DisplayFramebufferScale = { 1.0f, 1.0f };

		glViewport(0, 0, _event.GetWidth(), _event.GetHeight());

		return false;
	}

}