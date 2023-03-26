#pragma once

#include "boomEngine/core/app.h"
#include "boomEngine/core/layer.h"
#include "boomEngine/events/eventClass.h"

#include "boomEngine/events/appEvent.h"
#include "boomEngine/events/keyEvent.h"
#include "boomEngine/events/mouseEvent.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_internal.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace bm {

	class BM_API ImGuiLayer : public layer {
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