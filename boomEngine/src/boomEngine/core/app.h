#pragma once

#include "bmpch.h"

#include "base.h"

#include "window.h"
#include "layerStack.h"
#include "boomEngine/events/eventClass.h"
#include "boomEngine/events/appEvent.h"

#include "boomEngine/core/timestep.h"

#include "boomEngine/ImGui/ImGuiLayer.h"

namespace bm {
	class app {
	public:
		app();
		virtual ~app();

		void pushLayer(layer* layer);
		void pushOverlay(layer* overlay);

		void onEvent(eventClass& e);

		void run();
		inline window& getWindow() { return *m_window; }
		inline static app& getApp() { return *s_instance; }
	private:
		bool onWindowClose(windowCloseEvent& e);

		bool m_running = false;
		scope<window> m_window;
		layerStack m_layerStack;
		ImGuiLayer* m_ImGuiLayer;

		float m_lastFrameTime = 0.0f;

		static app* s_instance;
	};

	// to be defined in client 
	app* createApp();
}