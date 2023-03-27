#pragma once

#include "boomEngine/core/layer.h"
#include "boomEngine/events/eventClass.h"

#include "boomEngine/events/appEvent.h"
#include "boomEngine/events/keyEvent.h"
#include "boomEngine/events/mouseEvent.h"

namespace bm {

	class ImGuiLayer : public layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiDraw() override;

		void begin();
		void end();
	private:
		float m_time = 0.0f;
	};
}