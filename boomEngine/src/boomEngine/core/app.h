#pragma once

#include "bmpch.h"

#include "base.h"

#include "window.h"
#include "layerStack.h"
#include "boomEngine/events/eventClass.h"
#include "boomEngine/events/appEvent.h"

#include "input.h"

#include <glad/glad.h>

namespace bm {
	class BM_API app {
	public:
		app();
		virtual ~app();

		void pushLayer(layer* layer);
		void pushOverlay(layer* overlay);

		void onEvent(eventClass& e);

		void run();
		inline window& getWindow() { return *m_window; }
		static app& getApp();
	private:
		bool m_running = false;
		bool onWindowClose(windowCloseEvent& e);
		std::unique_ptr<window> m_window;
		layerStack m_layerStack;
	};

	// to be defined in client 
	app* createApp();
}