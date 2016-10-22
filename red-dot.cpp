#include <obs-module.h>
#include <thread>

static bool isShowingDot = false;
static bool shouldShowDot = true;

struct RedDotStruct {
	std::thread DotThread;

	void mainLoop();
	bool isStreaming();
	bool isRecording();
	static void showDot();
	static void hideDot();
	void Start();
	void Stop();

	inline ~RedDotStruct() {
		Stop();
	}
};

static RedDotStruct *RedDotObj = nullptr;

OBS_DECLARE_MODULE();

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

bool obs_module_load(void) {
	blog(LOG_DEBUG, "Loading RedDot");
	RedDotObj = new RedDotStruct;
	RedDotObj->Start();
	return true;
}

void obs_module_unload() {
	blog(LOG_DEBUG, "Unloading RedDot");
	delete RedDotObj;
	RedDotObj = nullptr;
}

const char *obs_module_author(void) {
	return "AfzalivE";
}

const char *obs_module_name(void) {
	return "Red Dot";
}

const char *obs_module_description(void) {
	return "Shows recording notification";
}

void RedDotStruct::mainLoop() {
	blog(LOG_DEBUG, "MainLoop");
	bool streamOutputting = false;
	bool recordOutputting = false;

	while (true) {
		if ((!streamOutputting && isStreaming())
			|| (!recordOutputting && isRecording())) {
			if (shouldShowDot && !isShowingDot) {
				showDot();
			}
		}
		else {
			if (isShowingDot) {
				hideDot();
			}
		}
	}
}

void RedDotStruct::Start() {
	blog(LOG_DEBUG, "Start()");
	RedDotObj->DotThread = std::thread([]() {
		RedDotObj->mainLoop();
	});
}

void RedDotStruct::Stop() {
	blog(LOG_DEBUG, "Stop()");
	if (DotThread.joinable()) {
		DotThread.join();
	}
}

bool RedDotStruct::isStreaming() {
	return obs_output_active(obs_get_output_by_name("simple_stream"))
		|| obs_output_active(obs_get_output_by_name("adv_stream"));
}

bool RedDotStruct::isRecording() {
	return obs_output_active(obs_get_output_by_name("simple_file_output"))
		|| obs_output_active(obs_get_output_by_name("adv_file_output"))
		|| obs_output_active(obs_get_output_by_name("adv_ffmpeg_output"));
}

void RedDotStruct::showDot() {
	blog(LOG_DEBUG, "Show dot");
	isShowingDot = true;
	shouldShowDot = false;
}

void RedDotStruct::hideDot() {
	blog(LOG_DEBUG, "Hide dot");
	isShowingDot = false;
	shouldShowDot = true;
}