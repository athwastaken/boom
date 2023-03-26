#include "bmpch.h"

#include "windowsWindow.h"

#include "boomEngine/events/appEvent.h"
#include "boomEngine/events/keyEvent.h"
#include "boomEngine/events/mouseEvent.h"

#include <glad/glad.h>

namespace bm {
	static bool s_glfwInitialized = false;

	static void glfwErrorCallback(int error, const char* desc) {
		BM_CORE_ERROR("GLFW error ({0}): {1}", error, desc);
	};

	window* window::create(const windowProps& props) {
		return new windowsWindow(props);
	}

	windowsWindow::windowsWindow(const windowProps& props) {
		init(props);
	}

	windowsWindow::~windowsWindow() {
		shutdown();
	}

	void windowsWindow::init(const windowProps& props) {
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		BM_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!s_glfwInitialized) {
			int success = glfwInit();
			BM_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(glfwErrorCallback);

			s_glfwInitialized = true;
		}

		m_window = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BM_CORE_ASSERT(success, "Failed to initialize Glad.");
		glfwSetWindowUserPointer(m_window, &m_data);
		vsync(true);

		// set glfw callbacks

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			windowResizeEvent event(width, height);

			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

			windowCloseEvent event;

			data.eventCallback(event);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					keyPressedEvent event(key, false);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					keyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					keyPressedEvent event(key, true);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
			keyTypedEvent event(keycode);
			data.eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					mouseButtonPressedEvent event(button);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					mouseButtonReleasedEvent event(button);
					data.eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double offsetX, double offsetY) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

			mouseScrolledEvent event((float)offsetX, (float)offsetY);
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double posX, double posY) {
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

			mouseMovedEvent event((float)posX, (float)posY);
			data.eventCallback(event);
		});
	}
	
	void windowsWindow::shutdown() {
		glfwDestroyWindow(m_window);
	}

	void windowsWindow::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void windowsWindow::vsync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.vsync = enabled;
	}

	bool windowsWindow::isVsync() const {
		return m_data.vsync;
	}
}
