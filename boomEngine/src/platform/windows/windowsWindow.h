#pragma once

#include "boomEngine/core/window.h"

#include <glfw/glfw3.h>

namespace bm {
	class windowsWindow : public window {
	public:
		windowsWindow(const windowProps& props);
		virtual ~windowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_data.width; }
		inline unsigned int getHeight() const override { return m_data.height; }

		// window attributes

		inline void eventCallback(const eventCallbackFn& callback) override { m_data.eventCallback = callback; }
		void vsync(bool enabled) override;
		bool isVsync() const override;

		inline virtual void* getNativeWindow() const { return m_window; }
	private:
		virtual void init(const windowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* m_window;

		struct windowData {
			std::string title;
			unsigned int width, height;
			bool vsync;

			eventCallbackFn eventCallback;
		};

		windowData m_data;
	};
}