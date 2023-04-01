#pragma once

#include "boomEngine/draw/context.h"

struct GLFWwindow;

namespace bm {
	class OpenGLContext : public draw::context {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void init() override;
		virtual void swapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}
