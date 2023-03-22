#include <boomEngine.h>

class BM_API boomGame : public bm::app {

public:
	boomGame() {
		pushOverlay(new bm::imguiLayer());
	}

	~boomGame() {

	}
};

bm::app * bm::createApp() {
	return new boomGame();
}