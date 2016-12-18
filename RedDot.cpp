#include <obs-module.h>
#include <obs-frontend-api.h>
#include "RtssInterface.h"

RtssInterface* rtss;

OBS_DECLARE_MODULE();

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

void showDot() {
	blog(LOG_DEBUG, "Show dot");
	rtss->showDot();
}

void hideDot() {
	blog(LOG_DEBUG, "Hide dot");
	rtss->hideDot();
}

void reddot_frontend_event_callback(enum obs_frontend_event event, void *private_data) {
	blog(LOG_DEBUG, "Callback");
	if (event == OBS_FRONTEND_EVENT_RECORDING_STARTED) {
		showDot();
	}
	else if (event == OBS_FRONTEND_EVENT_RECORDING_STOPPED) {
		hideDot();
	}
}

bool obs_module_load(void) {
	blog(LOG_DEBUG, "Loading RTSS Interface");
	blog(LOG_DEBUG, "Loading RedDot");
	obs_frontend_add_event_callback(reddot_frontend_event_callback, 0);
	return true;
}

void obs_module_unload() {
	blog(LOG_DEBUG, "Unloading RedDot");
	delete rtss;
	rtss = nullptr;
}

const char *obs_module_author(void) {
	return "AfzalivE";
}

const char *obs_module_name(void) {
	return "Red Dot";
}

const char *obs_module_description(void) {
	return "Shows a dot using RTSS when recording.";
}