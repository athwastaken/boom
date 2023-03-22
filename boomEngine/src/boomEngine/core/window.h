#pragma once

#include "bmpch.h"

#include "base.h"
#include "boomEngine/events/eventClass.h"

namespace bm {
	struct windowProps {
		std::string title;
		unsigned int width;
		unsigned int height;

		windowProps(const std::string& title = "Boom Engine", unsigned int width = 1280, unsigned int height = 720) : title(title), width(width), height(height) {

		}
	};

	// interface representing a desktop window
	class BM_API window {
	public:
		using eventCallbackFn = std::function<void(eventClass&)>;

		virtual ~window() {};
		virtual void onUpdate() = 0;
		
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// window attributes
		virtual void eventCallback(const eventCallbackFn& callback) = 0;
		virtual void vsync(bool enabled) = 0;
		virtual bool isVsync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static window* create(const windowProps& props = windowProps());
	};
}