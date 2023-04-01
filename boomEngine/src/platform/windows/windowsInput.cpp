#include "bmpch.h"
#include "WindowsInput.h"

#include "boomEngine/core/app.h"
#include <GLFW/glfw3.h>

namespace bm {
	input* input::s_instance = new windowsInput();

	bool windowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(app::getApp().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool windowsInput::isMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(app::getApp().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	
	std::pair<float, float> windowsInput::getMousePosImpl() {
		auto window = static_cast<GLFWwindow*>(app::getApp().getWindow().getNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}

	float windowsInput::getMouseXImpl() {
		auto [x, y] = getMousePosImpl();

		return x;
	}

	float windowsInput::getMouseYImpl() {
		auto [x, y] = getMousePosImpl();

		return y;
	}
}