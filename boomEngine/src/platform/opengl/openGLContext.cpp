#include "bmpch.h"
#include "OpenGLContext.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace bm {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle) {
		BM_CORE_ASSERT(windowHandle, "Window handle is null.")
	}

	void OpenGLContext::init() {
		glfwMakeContextCurrent(m_windowHandle);
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BM_CORE_ASSERT(success, "Failed to initialize Glad.");

		BM_CORE_INFO("OpenGL Info:");
		
		BM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		BM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		BM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}
}