#pragma once

#include "bmpch.h"

#include "boomEngine/core/base.h"

namespace bm {

	// currently using blocking method

	enum class eventType {
		none = 0,
		windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,
		appTick, appUpdate, appRender,
		keyPressed, keyReleased, keyTyped,
		mouseMoved, mouseScrolled,
		mouseButtonPressed, mouseButtonReleased
	};

	enum eventCategory {
		none = 0,
		eventCategoryApp = BIT(0),
		eventCategoryInput = BIT(1),
		eventCategoryKeyboard = BIT(2),
		eventCategoryMouse = BIT(3),
		eventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)	static eventType getStaticType() { return eventType::type; }\
								virtual eventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class eventClass {
		friend class eventDispatcher;
	public:
		virtual eventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		bool isInCategory(eventCategory category) {
			return getCategoryFlags() & category;
		}
		bool m_handled = false;
	};
	class eventDispatcher {
		template<typename T>
		using eventFn = std::function<bool(T&)>;
	public:
		eventDispatcher(eventClass& e)
			: m_event(e) {};

		template<typename T>

		bool dispatchEvent(eventFn<T> func) {
			if (m_event.getEventType() == T::getStaticType()) {
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	private:
		eventClass& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const eventClass& e) {
		return os << e.toString();
	};
}