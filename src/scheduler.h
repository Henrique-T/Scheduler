#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "process.h"

using namespace std;

/*
	Manages processes and their contexts, based on a chosen algorithm.
	The algorithm is chosen by the user through the command line.
*/
class scheduler
{
public:
	scheduler(/* args */);
	~scheduler();
	/**/
	int FCFS(/* args */);
	/**/
	int shortestJobFirst(/* args */);
	/**/
	int priorityWithoutPreemption(/* args */);
	/**/
	int priorityWithPreemption(/* args */);
	/**/
	int roundRobin(/* args */);

private:
	/* data */
	vector<process> processes;
};

#endif