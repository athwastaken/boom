#pragma once

#include "eventClass.h"

namespace bm {
	class BM_API keyEvent : public eventClass {
	public:
		inline int getKeyCode() const { return m_keyCode; }
		EVENT_CLASS_CATEGORY(eventCategoryKeyboard | eventCategoryInput)
			
	protected:
		keyEvent(int keycode) : m_keyCode(keycode) {};
		int m_keyCode;
	};

	class BM_API keyPressedEvent : public keyEvent {
	public:
		keyPressedEvent(int keycode, bool repeat)
			: keyEvent(keycode), m_repeat(repeat) {};

		inline bool repeat() const { return m_repeat; }

		std::string toString() const override {
			std::stringstream ss;
			ss << "keyPressedEvent: " << m_keyCode << " (key held down = " << m_repeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyPressed)
	private:
		bool m_repeat;
	};

	class BM_API keyTypedEvent : public keyEvent {
	public:
		keyTypedEvent(int keycode)
			: keyEvent(keycode) {};

		std::string toString() const override {
			std::stringstream ss;
			ss << "keyTypedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyTyped)
	};

	class BM_API keyReleasedEvent : public keyEvent {
	public:
		keyReleasedEvent(int keycode)
			: keyEvent(keycode) {};

		std::string toString() const override {
			std::stringstream ss;
			ss << "keyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(keyReleased)
	};
}