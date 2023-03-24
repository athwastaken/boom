#include <boomEngine.h>

class exampleLayer : public bm::layer {
public:
	exampleLayer() : layer("Example") {

	}

	void onUpdate() override {
		if (bm::input::isKeyPressed(BM_KEY_TAB)) {
			BM_TRACE("Tab pressed (poll).");
		}
	}

	void onEvent(bm::eventClass & e) override {
		if (e.getEventType() == bm::eventType::keyPressed) {
			bm::keyPressedEvent& keyEvent = (bm::keyPressedEvent&)e;
			if (keyEvent.getKeyCode() == BM_KEY_TAB) {
				BM_TRACE("Tab pressed (event).");
			}
		}
	}
};

class boomGame : public bm::app {

public:
	boomGame() {
		pushLayer(new exampleLayer());
		pushOverlay(new bm::imguiLayer());
	}

	~boomGame() {

	}
};

bm::app * bm::createApp() {
	return new boomGame();
}