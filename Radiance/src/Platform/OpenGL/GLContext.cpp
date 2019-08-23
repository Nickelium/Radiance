#include "pch.h"
#include "GLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Radiance/Renderer/API/RenderAPI.h"

namespace Radiance
{
	void GLAPIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei /*length*/,
		const GLchar* message, const void* /*userParam*/)
	{
		// ignore non-significant error/warning codes
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		RAD_CORE_FATAL("--- GL ERROR ---");
		RAD_CORE_FATAL("  Message: {0}", message);

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             RAD_CORE_FATAL("  Source: API"); break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   RAD_CORE_FATAL("  Source: Window System"); break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: RAD_CORE_FATAL("  Source: Shader Compiler"); break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     RAD_CORE_FATAL("  Source: Third Party"); break;
		case GL_DEBUG_SOURCE_APPLICATION:     RAD_CORE_FATAL("  Source: Application"); break;
		case GL_DEBUG_SOURCE_OTHER:           RAD_CORE_FATAL("  Source: Other"); break;
		} 

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               RAD_CORE_FATAL("  Type: Error"); break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: RAD_CORE_FATAL("  Type: Deprecated Behaviour"); break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  RAD_CORE_FATAL("  Type: Undefined Behaviour"); break;
		case GL_DEBUG_TYPE_PORTABILITY:         RAD_CORE_FATAL("  Type: Portability"); break;
		case GL_DEBUG_TYPE_PERFORMANCE:         RAD_CORE_FATAL("  Type: Performance"); break;
		case GL_DEBUG_TYPE_MARKER:              RAD_CORE_FATAL("  Type: Marker"); break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          RAD_CORE_FATAL("  Type: Push Group"); break;
		case GL_DEBUG_TYPE_POP_GROUP:           RAD_CORE_FATAL("  Type: Pop Group"); break;
		case GL_DEBUG_TYPE_OTHER:               RAD_CORE_FATAL("  Type: Other"); break;
		} 

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:			RAD_CORE_FATAL("  Severity: high"); break;
		case GL_DEBUG_SEVERITY_MEDIUM:			RAD_CORE_FATAL("  Severity: medium"); break;
		case GL_DEBUG_SEVERITY_LOW:				RAD_CORE_FATAL("  Severity: low"); break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:	RAD_CORE_FATAL("  Severity: notification"); break;
		} 

		RAD_CORE_ASSERT(false, "--- GL ERROR ---");
	}

	GLContext::GLContext(GLFWwindow* _windowHandle)
		: m_WindowHandle(_windowHandle)
	{
		RAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");	
	}

	void GLContext::Init()
	{
		RAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RAD_CORE_ASSERT(status, "Failed to initialize Glad");
		RAD_CORE_TRACE("{0}", "Glad Initialized");

		std::string vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		std::string renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		std::string version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

		auto& api = RenderAPI::GetAPI();
		api.data = { vendor, renderer, version };

		RAD_CORE_INFO("Manufacturer GPU Info:");
		RAD_CORE_INFO("  Vendor: {0}", vendor);
		RAD_CORE_INFO("  Renderer: {0}", renderer);
		RAD_CORE_INFO("  Version: {0}", version);

		#if defined(DEBUG) || defined(_DEBUG)
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			// Otherwise won't indicate at exact glCall
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(&GLDebugCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
		#endif

	}

	void GLContext::SwapBuffers()
	{
		RAD_CORE_ASSERT(m_WindowHandle, "Windows Handle is nullptr");
		glfwSwapBuffers(m_WindowHandle);
	}

}