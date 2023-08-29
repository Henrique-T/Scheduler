#include "Scheduler.h"

Scheduler::Scheduler(vector<Process> _processes, string _algorithm)
{
	this->processes = _processes;
	this->algorithm = _algorithm;

	if (this->algorithm == "FCFS")
	{
		/* code */
		this->FCFS();
	}
	else if (this->algorithm == "shortestJobFirst")
	{
		/* code */
		this->shortestJobFirst();
	}
	else if (this->algorithm == "priorityWithoutPreemption")
	{
		/* code */
		this->priorityWithoutPreemption();
	}
	else if (this->algorithm == "priorityWithPreemption")
	{
		/* code */
		this->priorityWithPreemption();
	}
	else if (this->algorithm == "roundRobin")
	{
		/* code */
		this->roundRobin();
	}
	else
	{
		throw "Not a valid algorithm!";
	}
}

Scheduler::~Scheduler()
{
}

/////////////// Scheduling Algorithms ///////////////

int Scheduler::FCFS(/* args */)
{
	return 0;
}

int Scheduler::shortestJobFirst(/* args */)
{
	return 0;
}

int Scheduler::priorityWithoutPreemption(/* args */)
{
	return 0;
}

int Scheduler::priorityWithPreemption(/* args */)
{
	return 0;
}

int Scheduler::roundRobin(/* args */)
{
	return 0;
}
