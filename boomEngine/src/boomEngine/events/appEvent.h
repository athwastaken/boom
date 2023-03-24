#pragma once

#include "eventClass.h"

namespace bm {
	class BM_API windowResizeEvent : public eventClass {
	public:
		windowResizeEvent(unsigned int windowWidth, unsigned int windowHeight)
			: m_windowWidth(windowWidth), m_windowHeight(windowHeight) {};

		inline unsigned int getWindowWidth() const { return m_windowWidth; }
		inline unsigned int getWindowHeight() const { return m_windowHeight; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "windowResizeEvent: " << m_windowWidth << ", " << m_windowHeight;
			return ss.str();
		}

		EVENT_CLASS_TYPE(windowResize)
		EVENT_CLASS_CATEGORY(eventCategoryApp)
	private:
		unsigned int m_windowWidth, m_windowHeight;
	};

	class BM_API windowCloseEvent : public eventClass {
	public:
		windowCloseEvent() {};

		EVENT_CLASS_TYPE(windowClose)
		EVENT_CLASS_CATEGORY(eventCategoryApp)
	};

	class BM_API appTickEvent : public eventClass {
	public:
		appTickEvent() {};

		EVENT_CLASS_TYPE(appTick)
		EVENT_CLASS_CATEGORY(eventCategoryApp)
	};

	class BM_API appUpdateEvent : public eventClass {
	public:
		appUpdateEvent() {};

		EVENT_CLASS_TYPE(appUpdate)
		EVENT_CLASS_CATEGORY(eventCategoryApp)
	};

	class BM_API appRenderEvent : public eventClass {
	public:
		appRenderEvent() {};

		EVENT_CLASS_TYPE(appRender)
		EVENT_CLASS_CATEGORY(eventCategoryApp)
	};
}