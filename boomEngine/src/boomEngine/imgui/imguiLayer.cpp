#include "bmpch.h"
#include "imguiLayer.h"

// temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace bm {
	imguiLayer::imguiLayer() : layer("imguiLayer") {

	}

	imguiLayer::~imguiLayer() {

	}

	void imguiLayer::onAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// temp



		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void imguiLayer::onDetach() {
	}

	void imguiLayer::onUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		app& a = app::getApp();
		io.DisplaySize = ImVec2(a.getWindow().getWidth(), a.getWindow().getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0 ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void imguiLayer::onEvent(eventClass& e) {
		eventDispatcher dispatcher(e);
		dispatcher.dispatchEvent<mouseButtonPressedEvent>(BM_BIND_EVENT_FN(imguiLayer::onMouseButtonPressedEvent));
		dispatcher.dispatchEvent<mouseButtonReleasedEvent>(BM_BIND_EVENT_FN(imguiLayer::onMouseButtonReleasedEvent));
		dispatcher.dispatchEvent<mouseMovedEvent>(BM_BIND_EVENT_FN(imguiLayer::onMouseMovedEvent));
		dispatcher.dispatchEvent<keyPressedEvent>(BM_BIND_EVENT_FN(imguiLayer::onKeyPressedEvent));
		dispatcher.dispatchEvent<keyTypedEvent>(BM_BIND_EVENT_FN(imguiLayer::onKeyTypedEvent));
		dispatcher.dispatchEvent<keyReleasedEvent>(BM_BIND_EVENT_FN(imguiLayer::onKeyReleasedEvent));
		dispatcher.dispatchEvent<windowResizeEvent>(BM_BIND_EVENT_FN(imguiLayer::onWindowResizeEvent));
	}

	bool imguiLayer::onMouseButtonPressedEvent(mouseButtonPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = true;

		return false;
	}

	bool imguiLayer::onMouseButtonReleasedEvent(mouseButtonReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = false;

		return false;
	}

	bool imguiLayer::onMouseMovedEvent(mouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.getMouseX(), e.getMouseY());

		return false;
	}

	bool imguiLayer::onMouseScrolledEvent(mouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.getOffsetX();
		io.MouseWheel += e.getOffsetY();

		return false;
	}

	bool imguiLayer::onKeyPressedEvent(keyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		
		return false;
	}

	bool imguiLayer::onKeyTypedEvent(keyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.getKeyCode();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}

	bool imguiLayer::onKeyReleasedEvent(keyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = false;

		return false;
	}

	bool imguiLayer::onWindowResizeEvent(windowResizeEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.getWindowWidth(), e.getWindowHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.getWindowWidth(), e.getWindowHeight());

		return false;
	}
}
