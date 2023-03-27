#pragma once

#include "base.h"
#include "boomEngine/events/eventClass.h"

namespace bm {
	class layer {
	public:
		layer(const std::string& name = "Layer");
		virtual ~layer() = default;

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate() {};
		virtual void onImGuiDraw() {};
		virtual void onEvent(eventClass& e) {};

		inline const std::string& name() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};
}

