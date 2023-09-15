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
	vector<Process> heap;
	vector<ProcessParams *> rawProcesses;
	string algorithm;
	int heapSize;
	int currentTime;

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
	int getHeapSize();
	/**/
	int getCurrentTime();
	/**/
	void setRawProcesses(vector<ProcessParams *> _rawProcesses);
	/**/
	void setProcesses(vector<Process> _processes);
	/**/
	void setAlgorithm(string _algorithm);
	/**/
	void setHeapSize(int _heapSize);
	/**/
	void setCurrentTime(int _currentTime);
	/**/
	void insertProcess(Process _process);
	/**/
	void insertProcessToHeap(Process _process);
	/**/
	void orderHeap(int _start);
	/**/
	Process extractminimum();
	/**/
	static bool compareDurations(const Process &a, const Process &b);
	/**/
	static bool compareArrivalTimes(const Process &a, const Process &b);
	/**/
	void executeHighestPriorityFromHeap();
	/**/
	void manage();
	/* Pretty prints the final result */
	void printHeaders();
	/* Pretty prints the final result */
	void printRow(int _currentTime, Process executingProcess, Process preemptedProces = Process());
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