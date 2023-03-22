#pragma once

#include "eventClass.h"

namespace bm {
	class BM_API mouseMovedEvent : public eventClass {
	public:
		mouseMovedEvent(float posX, float posY)
			: m_posX(posX), m_posY(posY) {};

		inline float mouseX() const { return m_posX; }
		inline float mouseY() const { return m_posY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseMovedEvent: " << m_posX << ", " << m_posY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseMoved)
		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
	private:
		float m_posX, m_posY;
	};

	class BM_API mouseScrolledEvent : public eventClass {
	public:
		mouseScrolledEvent(float offsetX, float offsetY)
			: m_offsetX(offsetX), m_offsetY(offsetY) {};

		inline float offsetX() const { return m_offsetX; }
		inline float offsetY() const { return m_offsetY; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseScrolledEvent: " << offsetX() << ", " << offsetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseScrolled)
		EVENT_CLASS_CATEGORY(eventCategoryMouse | eventCategoryInput)
	private:
		float m_offsetX, m_offsetY;
	};

	class BM_API mouseButtonEvent : public eventClass {
	public:
		inline int mouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(eventCategoryMouseButton | eventCategoryMouse | eventCategoryInput)
	protected:
		mouseButtonEvent(int button)
			: m_button(button) {};

		int m_button;
	};

	class BM_API mouseButtonPressedEvent : public mouseButtonEvent {
	public:
		mouseButtonPressedEvent(int button)
			: mouseButtonEvent(button) {};

		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseButtonPressed)
	};

	class BM_API mouseButtonReleasedEvent : public mouseButtonEvent {
	public:
		mouseButtonReleasedEvent(int button)
			: mouseButtonEvent(button) {};
		std::string toString() const override {
			std::stringstream ss;
			ss << "mouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(mouseButtonReleased)
	};
}