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
	std::vector<Process*> getProcessesCreatedByTime(int _currentTime);
	/**/
	string getAlgorithm();
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
	static bool compareProcessesByStaticPriorityAsc(const Process* a, const Process* b);
	/**/
	static bool compareProcessesByDurationDesc(const Process* a, const Process* b);
	/* Pretty prints the final result */
	void printHeaders();
	/* Pretty time tick execution row */
	void printRow(int _currentTime, int _executingProcessPid, int _preemptedProcessPid);
	/* Printing final stats */
	void printFinalStats(int _numberofContextSwitches);
	/**/
	int FCFS();
	/**/
	int shortestJobFirst();
	/**/
	int priorityWithoutPreemption();
	/**/
	int priorityWithPreemption();
	/**/
	int roundRobin();
};

#endif