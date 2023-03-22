#pragma once

#include "bmpch.h"

#include "boomEngine/core/base.h"

namespace bm {

	// currently using blocking method

	enum class enumEventType {
		none = 0,
		windowClose, windowResize, windowFocus, windowLostFocus, windowMoved,
		appTick, appUpdate, appRender,
		keyPressed, keyReleased, keyTyped,
		mouseMoved, mouseScrolled,
		mouseButtonPressed, mouseButtonReleased
	};

	enum enumEventCategory {
		none = 0,
		eventCategoryApp = BIT(0),
		eventCategoryInput = BIT(1),
		eventCategoryKeyboard = BIT(2),
		eventCategoryMouse = BIT(3),
		eventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)	static enumEventType staticType() { return enumEventType::##type; }\
								virtual enumEventType eventType() const override { return staticType(); }\
								virtual const char* name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int categoryFlags() const override { return category; }

	class BM_API eventClass {
		friend class eventDispatcher;
	public:
		virtual enumEventType eventType() const = 0;
		virtual const char* name() const = 0;
		virtual int categoryFlags() const = 0;
		virtual std::string toString() const { return name(); }

		inline bool isInCategory(enumEventCategory category) {
			return categoryFlags() & category;
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
			if (m_event.eventType() == T::staticType()) {
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