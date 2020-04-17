#ifndef __PERF_INS_H_
#define __PERF_INS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "papi.h"

#define EVENT_SIZE 9

class Profiler {
	public:
		Profiler();
		~Profiler();
		void dumpInfo();
	private:
		int eventSet;

		// std::string eventName[EVENT_SIZE];
		long long start[EVENT_SIZE];
		long long end[EVENT_SIZE];
		long long values[EVENT_SIZE];
};

#endif
