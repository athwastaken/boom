#include "bmpch.h"
#include "openGLContext.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace bm {
	openGLContext::openGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle) {
		BM_CORE_ASSERT(windowHandle, "Window handle is null.")
	}

	void openGLContext::init() {
		glfwMakeContextCurrent(m_windowHandle);
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BM_CORE_ASSERT(success, "Failed to initialize Glad.");
	}

	void openGLContext::swapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}
}