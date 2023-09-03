#include "Scheduler.h"
#include <map>
#include <string>

using namespace std;

Scheduler::Scheduler() {}

Scheduler::Scheduler(vector<Process> _processes, string _algorithm)
{
	this->setProcesses(_processes);
	this->setAlgorithm(_algorithm);

	if (_algorithm == "FCFS")
	{
		/* code */
		this->FCFS();
	}
	else if (_algorithm == "shortestJobFirst")
	{
		/* code */
		this->shortestJobFirst();
	}
	else if (_algorithm == "priorityWithoutPreemption")
	{
		/* code */
		this->priorityWithoutPreemption();
	}
	else if (_algorithm == "priorityWithPreemption")
	{
		/* code */
		this->priorityWithPreemption();
	}
	else if (_algorithm == "roundRobin")
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

/////////////// Scheduling Algorithms and helpers ///////////////

int Scheduler::FCFS(/* args */)
{
	// Find the wait time and turn around time for each and all processes
	this->getProcesses().at(0).getContext().setWaitingTime(0);
	this->getProcesses().at(0).getContext().setTurnAroundTime(
		this->getProcesses().at(0).getContext().getDuration() +
		this->getProcesses().at(0).getContext().getWaitingTime());

	for (size_t i = 1; i < this->getProcesses().size(); i++)
	{
		int previousDurationTime = this->getProcesses().at(i - 1).getContext().getDuration();
		int previousWaitingTime = this->getProcesses().at(i - 1).getContext().getWaitingTime();
		this->getProcesses().at(i).getContext().setWaitingTime(
			previousDurationTime + previousWaitingTime);
		int duration = this->getProcesses().at(i).getContext().getDuration();
		int waitingTime = this->getProcesses().at(i).getContext().getWaitingTime();
		this->getProcesses().at(i).getContext().setTurnAroundTime(duration + waitingTime);
	}

	// Find average time
	int totalWaitingTime = 0, totalTurnAroundTime = 0;
	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		totalWaitingTime = totalWaitingTime + this->getProcesses().at(i).getContext().getWaitingTime();
		totalTurnAroundTime = totalTurnAroundTime +
							  this->getProcesses().at(i).getContext().getTurnAroundTime();
	}

	cout << "Average waiting time = "
		 << (float)totalWaitingTime / (float)this->getProcesses().size();
	cout << "\nAverage turn around time = "
		 << (float)totalTurnAroundTime / (float)this->getProcesses().size() << "\n";

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

void Scheduler::findTurnAroundTimeForEach() {}
void Scheduler::findWaitingTimeForEach() {}
void Scheduler::findTotalTimesOfContextChangeForEach() {}
void Scheduler::findAverageTurnAroundTime() {}
void Scheduler::findAverageWaitingTime() {}
void Scheduler::findAverageTimesOfContextChange() {}

/////////////// gets ///////////////

vector<Process> Scheduler::getProcesses() { return this->processes; }

Process Scheduler::getProcessByPid(pid_t _pid)
{
	if (!this->doesProcessExist(_pid))
	{
		throw "Process does not exist";
	}

	int size = this->getProcesses().size();
	for (int i = 0; i < size; i++)
	{
		if (this->getProcesses().at(i).getPid() == _pid)
		{
			return this->getProcesses().at(i);
		}
	}
	Process n;
	return n; // returning an empty process may be dangerous.
}

string Scheduler::getAlgorithm() { return this->algorithm; }

bool Scheduler::doesProcessExist(pid_t _pid)
{
	int size = this->getProcesses().size();
	for (int i = 0; i < size; i++)
	{
		if (this->getProcesses().at(i).getPid() == _pid)
		{
			return true;
		}
	}
	return false;
}

/////////////// sets ///////////////

void Scheduler::setProcesses(vector<Process> _processes)
{
	this->processes = _processes;
}

void Scheduler::setAlgorithm(string _algorithm)
{
	this->algorithm = _algorithm;
}

/////////////// beautifiers ///////////////

void Scheduler::prettyPrint(string _statusp1, string _statusp2, string _statusp3, string _statusp4)
{
	cout << "tempo"
		 << "   "
		 << "P1"
		 << "   "
		 << "P2"
		 << "   "
		 << "P3"
		 << "   "
		 << "P4\n";

	// relate status and symbol
	std::map<string, string> mapStatusAndSymbol;
	const char *ready = "ready";		 // process has been created and it's waiting.
	const char *executing = "executing"; // process is executing
	const char *notReady = "done";		 // process hasn't started or it's done.
	const char *hashtag = "##";
	const char *douleDash = "--";
	const char *emptySpace = " ";
	mapStatusAndSymbol.insert(std::make_pair(ready, douleDash));
	mapStatusAndSymbol.insert(std::make_pair(executing, hashtag));
	mapStatusAndSymbol.insert(std::make_pair(notReady, emptySpace));

	int sumOfProcessDuration = 14; // in the future, make it dynamic
	for (int i = 0; i < sumOfProcessDuration; i++)
	{
		int left = i;
		int right = left + 1;
		if (i < 9)
		{
			cout << left << " " << right << "     "
				 << mapStatusAndSymbol[_statusp1]
				 << "   "
				 << mapStatusAndSymbol[_statusp2]
				 << "   "
				 << mapStatusAndSymbol[_statusp3]
				 << "   "
				 << mapStatusAndSymbol[_statusp4]
				 << "\n";
		}
		else if (i == 9)
		{
			cout << left << " " << right << "    "
				 << mapStatusAndSymbol[_statusp1]
				 << "   "
				 << mapStatusAndSymbol[_statusp2]
				 << "   "
				 << mapStatusAndSymbol[_statusp3]
				 << "   "
				 << mapStatusAndSymbol[_statusp4]
				 << "\n";
		}
		else
		{
			cout << left << " " << right << "   "
				 << mapStatusAndSymbol[_statusp1]
				 << "   "
				 << mapStatusAndSymbol[_statusp2]
				 << "   "
				 << mapStatusAndSymbol[_statusp3]
				 << "   "
				 << mapStatusAndSymbol[_statusp4]
				 << "\n";
		}
	}
}