#pragma once

#include "base.h"
#include "boomEngine/events/eventClass.h"
#include "timestep.h"

namespace bm {
	class layer {
	public:
		layer(const std::string& name = "Layer");
		virtual ~layer() {};

		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate(timestep ts) {};
		virtual void onImGuiDraw() {};
		virtual void onEvent(eventClass& e) {};

		inline const std::string& getName() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};
}

