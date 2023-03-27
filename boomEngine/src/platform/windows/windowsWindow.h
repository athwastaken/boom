#pragma once

#include "boomEngine/core/window.h"
#include "boomEngine/draw/context.h"

#include <glfw/glfw3.h>

namespace bm {
	class windowsWindow : public window {
	public:
		windowsWindow(const windowProps& props);
		virtual ~windowsWindow();

		virtual void onUpdate() override;

		virtual unsigned int getWidth() const override { return m_data.width; }
		virtual unsigned int getHeight() const override { return m_data.height; }

		// window attributes

		virtual void setEventCallback(const eventCallbackFn& callback) override { m_data.setEventCallback = callback; }
		virtual void setVsync(bool enabled) override;
		virtual bool isVsync() const override;

		virtual void* getNativeWindow() const { return m_window; }
	private:
		virtual void init(const windowProps& props);
		virtual void shutdown();

		GLFWwindow* m_window;
		draw::context* m_context;
		struct windowData {
			std::string title;
			unsigned int width, height;
			bool vsync;

			eventCallbackFn setEventCallback;
		};

		windowData m_data;
	};
}