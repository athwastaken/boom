#pragma once

#include "bmpch.h"

#include "../../boomEngine.h"

#ifdef BM_PLATFORM_WINDOWS

extern bm::app* bm::createApp();

int main(int argc, char** argv) {
	bm::log::init();
	BM_CORE_INFO("Initialized Log");

	bm::app* rp_boom = bm::createApp();
	rp_boom->run();
	delete rp_boom;
	return 0;
}

#endif