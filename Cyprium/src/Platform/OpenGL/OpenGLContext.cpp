#include "cppch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include <gl/GL.h>

namespace Cyprium
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		CP_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CP_CORE_ASSERT(status, "Failed to initialize Glad!");

		CP_CORE_INFO("OpenGL Renderer");
		CP_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CP_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CP_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}