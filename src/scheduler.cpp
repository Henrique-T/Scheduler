#include "scheduler.h"

scheduler::scheduler(vector<process> _processes, string _algorithm)
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

scheduler::~scheduler()
{
}

/////////////// Scheduling Algorithms ///////////////

int scheduler::FCFS(/* args */)
{
	return 0;
}

int scheduler::shortestJobFirst(/* args */)
{
	return 0;
}

int scheduler::priorityWithoutPreemption(/* args */)
{
	return 0;
}

int scheduler::priorityWithPreemption(/* args */)
{
	return 0;
}

int scheduler::roundRobin(/* args */)
{
	return 0;
}
