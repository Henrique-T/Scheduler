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
	vector<Process> processes;
	vector<Process> heap;
	vector<ProcessParams *> rawProcesses;
	string algorithm;
	int heapSize;
	int currentTime;

public:
	Scheduler();
	/* 
	Constructor. 
	Reads the file and creates a list of processes of type Process.
	Chooses what method to call based on algorithm. 
	*/
	Scheduler(string _algorithm);
	~Scheduler();
	/* Reads input file and creates a vector of processes. */
	void createProcesses();
	/* First Come First Served algorithm */
	int FCFS();
	/* Shortest Job First Algorithm */
	int shortestJobFirst();
	/* Priority Without Preemption Algorithm */
	int priorityWithoutPreemption();
	/* Priority With Preemption Algorithm */
	int priorityWithPreemption();
	/* Round Robin With Quantum = 2s algorithm*/
	int roundRobin();
	/* Inserts process to main list of processes */
	void insertProcess(Process _process);
	/* Inserts process to heap */
	void insertProcessToHeap(Process _process);
	/* Orders heap based on priority */
	void orderHeap(int _start);
	/* Finds the process with highest priority */
	Process extractminimum();
	/* Checks if priority of a is less than priority of b */
	static bool compareDurations(const Process &a, const Process &b);
	/* Checks if creation time of a is less than creation time of b */
	static bool compareCreationTimes(const Process &a, const Process &b);
	/* Executes the process with the highest priority in heap */
	void executeHighestPriorityFromHeap();
	/* Checks if process is in main process list */
	bool doesProcessExist(pid_t _pid);
	/* Pretty prints the final result */
	void prettyPrint(string _statusp1, string _statusp2, string _statusp3, string _statusp4);
	/* Pretty prints the final result */
	void printHeaders();
	/* Pretty prints the final result */
	void printRow(int _currentTime, int _executingProcessPid, int _preemptedProcessPid);
	/* Gets and Sets */
	vector<ProcessParams *> getRawProcesses();
	vector<Process> getProcesses();
	vector<Process> getProcessesCreatedByTime(int _currentTime);
	Process getProcessByPid(pid_t _pid);
	string getAlgorithm();
	int getHeapSize();
	int getCurrentTime();
	void setRawProcesses(vector<ProcessParams *> _rawProcesses);
	void setProcesses(vector<Process> _processes);
	void setAlgorithm(string _algorithm);
	void setHeapSize(int _heapSize);
	void setCurrentTime(int _currentTime);
};

#endif