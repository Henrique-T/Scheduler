#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <iostream>
#include <queue>
#include "Process.h"
#include "ProcessParams.h"

using namespace std;

/*
	Creates and manages processes and their contexts, based on a chosen algorithm.
	The algorithm is chosen by the user through the command line.
*/
class Scheduler
{
private:
	/* data */
	vector<Process> processes;
	vector<ProcessParams *> rawProcesses;
	string algorithm;

public:
	Scheduler();
	Scheduler(string _algorithm);
	~Scheduler();
	/* Reads input file and creates a vector of processes. */
	void createProcesses();
	/**/
	vector<Process> getProcesses();
	/**/
	Process getProcessByPid(pid_t _pid);
	/**/
	string getAlgorithm();
	/**/
	bool doesProcessExist(pid_t _pid);
	/**/
	vector<ProcessParams *> getRawProcesses();
	/**/
	void setRawProcesses(vector<ProcessParams *> _rawProcesses);
	/**/
	void setProcesses(vector<Process> _processes);
	/**/
	void setAlgorithm(string _algorithm);
	/**/
	void insertProcess(Process _process);
	/**/
	static bool compareDurations(const Process &a, const Process &b);
	/**/
	/* Pretty prints the final result */
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
	/**/
	void findTurnAroundTimeForEach();
	/**/
	void findWaitingTimeForEach();
	/**/
	void findTotalTimesOfContextChangeForEach();
	/**/
	void findAverageTurnAroundTime();
	/**/
	void findAverageWaitingTime();
	/**/
	void findAverageTimesOfContextChange();
};

#endif