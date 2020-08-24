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

		#ifdef CP_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			CP_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Cyprium requires at least OpenGL version 4.5!");
		#endif
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}