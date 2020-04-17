#ifndef __PERF_INS_H_
#define __PERF_INS_H_

#include <stdio.h>
#include <stdlib.h>
#include "papi.h"

#define EVENT_SIZE 4

class Profiler {
	public:
		Profiler();
		~Profiler();
		void dumpInfo();
	private:
		int eventSet;
		long long start[EVENT_SIZE];
		long long end[EVENT_SIZE];
		long long values[EVENT_SIZE];
};

#endif