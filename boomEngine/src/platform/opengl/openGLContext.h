#pragma once

#include "boomEngine/draw/context.h"

struct GLFWwindow;

namespace bm {
	class openGLContext : public draw::context {
	public:
		openGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}
