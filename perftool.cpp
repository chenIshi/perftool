#include "perftool.h"

Profiler profiler;

Profiler::Profiler() {
	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
		exit(-1);
	}
	eventSet = PAPI_NULL;

	if (PAPI_create_eventset(&eventSet) != PAPI_OK) {
		exit(-1);
	}

	if (PAPI_add_event(eventSet, PAPI_BR_MSP) != PAPI_OK) {
		exit(-1);
	}
        
    if (PAPI_add_event(eventSet, PAPI_BR_CN) != PAPI_OK) {
		exit(-1);
	}
        
    if (PAPI_add_event(eventSet, PAPI_BR_PRC) != PAPI_OK) {
		exit(-1);
	}

	if (PAPI_start(eventSet) != PAPI_OK) {
		exit(-1);
	}
        
    if (PAPI_read(eventSet, start) != PAPI_OK) {
		exit(-1);
	}
}

Profiler::~Profiler() {
	if (PAPI_stop(eventSet, end) != PAPI_OK) {
		exit(-1);
	}

    if (PAPI_cleanup_eventset(eventSet) != PAPI_OK) {
		exit(-1);
	}

    if (PAPI_destroy_eventset(&eventSet) != PAPI_OK) {
		exit(-1);
	}

    PAPI_shutdown();
}

void Profiler::dumpInfo() {
	for (int i = 0; i , EVENT_SIZE; i++) {
		values[i] = end[i] - start[i];
	}
	fprintf(stdout, "%lld\n", values[i]);
}