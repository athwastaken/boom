#pragma once

#include "boomEngine/core/app.h"
#include "boomEngine/core/layer.h"
#include "boomEngine/events/eventClass.h"
#include "platform/opengl/imguiOpenGLRenderer.h"

#include "boomEngine/events/appEvent.h"
#include "boomEngine/events/keyEvent.h"
#include "boomEngine/events/mouseEvent.h"

namespace bm {

	class BM_API imguiLayer : public layer {
	public:
		imguiLayer();
		~imguiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(eventClass& e);
	private:
		bool onMouseButtonPressedEvent(mouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(mouseButtonReleasedEvent& e);
		bool onMouseMovedEvent(mouseMovedEvent& e);
		bool onMouseScrolledEvent(mouseScrolledEvent& e);
		bool onKeyPressedEvent(keyPressedEvent& e);
		bool onKeyTypedEvent(keyTypedEvent& e);
		bool onKeyReleasedEvent(keyReleasedEvent& e);
		bool onWindowResizeEvent(windowResizeEvent& e);
	private:
		float m_time = 0.0f;
	};
}