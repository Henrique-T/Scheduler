#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include "Process.h"

using namespace std;

/*
	Manages processes and their contexts, based on a chosen algorithm.
	The algorithm is chosen by the user through the command line.
*/
class Scheduler
{
private:
	/* data */
	vector<Process> processes;
	string algorithm;

public:
	Scheduler();
	Scheduler(vector<Process> _processes, string _algorithm);
	~Scheduler();
	/**/
	vector<Process> getProcesses();
	/**/
	Process getProcessByPid(pid_t _pid);
	/**/
	string getAlgorithm();
	/**/
	bool doesProcessExist(pid_t _pid);
	/**/
	void setProcesses(vector<Process> _processes);
	/**/
	void setAlgorithm(string _algorithm);
	/* Pretty print the final result */
	void prettyPrint(string _statusp1, string _statusp2, string _statusp3, string _statusp4);
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
};

#endif