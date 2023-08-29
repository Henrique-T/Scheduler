#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include "Process.h"

using namespace std;

/*
	Manages processes and their contexts, based on a chosen algorithm.
	The algorithm is chosen by the user through the command line.
*/
class Scheduler
{
public:
	Scheduler(vector<Process> _processes, string _algorithm);
	~Scheduler();
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
	vector<Process> processes;
	string algorithm;
};

#endif