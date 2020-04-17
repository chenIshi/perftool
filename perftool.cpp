#include "perftool.h"

Profiler profiler;
bool isInfoDumped = false;

using namespace std;

Profiler::Profiler() {

	// init data
	for (int i = 0; i<EVENT_SIZE; i++) {
		start[i] = 0;
		end[i] = 0;
		values[i] = 0;
	}

	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) {
		exit(-1);
	}
	eventSet = PAPI_NULL;

	if (PAPI_create_eventset(&eventSet) != PAPI_OK) {
		exit(-1);
	}

	// Branch Prediction Part
	// add perf event "Conditional branch instructions mispredicted"
	if (PAPI_add_event(eventSet, PAPI_BR_MSP) != PAPI_OK) {
		eventName[0] = "Cond Mispredicted Branch Inc";
		exit(-1);
	}
        
	// add perf event "Conditional branch instructions"
    if (PAPI_add_event(eventSet, PAPI_BR_CN) != PAPI_OK) {
		eventName[1] = "Cond Branch Inc";
		exit(-1);
	}
    
	// add perf event "Conditional branch instructions correctly predicted"
    if (PAPI_add_event(eventSet, PAPI_BR_PRC) != PAPI_OK) {
		eventName[2] = "Cond Predicted Branch Inc";
		exit(-1);
	}

	// CPI related
	// add perf event "Total cycles "
	if (PAPI_add_event(eventSet, PAPI_TOT_CYC) != PAPI_OK) {
		eventName[3] = "Total cycles ";
		exit(-1);
	}
	// add perf event "Instructions completed"
	if (PAPI_add_event(eventSet, PAPI_TOT_INS) != PAPI_OK) {
		eventName[4] = "Instructions completed";
		exit(-1);
	}

	// TLB related
	// add perf event "Data translation lookaside buffer misses"
	if (PAPI_add_event(eventSet, PAPI_TLB_DM) != PAPI_OK) {
		eventName[5] = "Data translation lookaside buffer misses";
		exit(-1);
	}
	// add perf event "Instruction translation lookaside buffer misses"
	if (PAPI_add_event(eventSet, PAPI_TLB_IM) != PAPI_OK) {
		eventName[6] = "Instruction translation lookaside buffer misses";
		exit(-1);
	}

	// L1-cache
	// add perf event "L1 total cache misses"
	if (PAPI_add_event(eventSet, PAPI_L1_TCM) != PAPI_OK) {
		eventName[7] = "L1 total cache misses";
		exit(-1);
	}

	// L2-cache
	// add perf event "L2 total cache misses"
	if (PAPI_add_event(eventSet, PAPI_L2_TCM) != PAPI_OK) {
		eventName[8] = "L2 total cache misses";
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
    if (!isInfoDumped) {
    	dumpInfo();
	isInfoDumped = true;
    }
    PAPI_shutdown();
}

void Profiler::dumpInfo() {
	printf("#### PAPI PERF #####\n");
	for (int i = 0; i < EVENT_SIZE; i++) {
		values[i] = end[i] - start[i];
		cout << eventName[i] << ": " << values[i] << endl;
	}
	printf("##################\n");
}
