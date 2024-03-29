#include "Scheduler.h"
#include "File.h"
#include <map>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

Scheduler::Scheduler() {}

Scheduler::Scheduler(string _algorithm)
{
	File f;
	f.read_file();
	this->setRawProcesses(f.getProcesses());
	this->createProcesses();
	this->setAlgorithm(_algorithm);
	this->setHeapSize(0);
	this->printHeaders();

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

Scheduler::~Scheduler() {}

/////////////// Creation of the processes list ///////////////

void Scheduler::createProcesses()
{
	/* this is where we start everything. */

	for (size_t i = 0; i < this->getRawProcesses().size(); i++)
	{
		ProcessParams *currentRawProcess = this->getRawProcesses().at(i);
		Process process(
			currentRawProcess->getCreationTime(),
			currentRawProcess->getDuration(),
			currentRawProcess->getPriority(), i);
		this->insertProcess(process);
	}
}

/////////////// Scheduling Algorithms and helpers ///////////////

int Scheduler::FCFS()
{
	this->processes.at(0).setWaitingTime(0);
	this->processes.at(0).setTurnAroundTime(
		this->processes.at(0).getContext().getDuration() +
		this->processes.at(0).getContext().getWaitingTime());

	for (size_t i = 1; i < this->getProcesses().size(); i++)
	{
		int previousDurationTime = this->getProcesses().at(i - 1).getContext().getDuration();
		int previousWaitingTime = this->getProcesses().at(i - 1).getContext().getWaitingTime();
		this->processes.at(i).setWaitingTime(
			previousDurationTime + previousWaitingTime);
		int duration = this->getProcesses().at(i).getContext().getDuration();
		int waitingTime = this->getProcesses().at(i).getContext().getWaitingTime();
		this->processes.at(i).setTurnAroundTime(duration + waitingTime);
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

	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		cout << this->getProcesses().at(i).getContext().getPid()
			 << " "
			 << this->getProcesses().at(i).getContext().getWaitingTime()
			 << " "
			 << this->getProcesses().at(i).getContext().getTurnAroundTime()
			 << "\n";
	}
	return 0;
}

int Scheduler::shortestJobFirst()
{
	// Sorting processes according to their Burst Time (duration).
	sort(this->processes.begin(), this->processes.end(), Scheduler::compareDurations);

	this->processes.at(0).setWaitingTime(0);
	this->processes.at(0).setTurnAroundTime(
		this->processes.at(0).getContext().getDuration() +
		this->processes.at(0).getContext().getWaitingTime());

	for (size_t i = 1; i < this->getProcesses().size(); i++)
	{
		int previousDurationTime = this->getProcesses().at(i - 1).getContext().getDuration();
		int previousWaitingTime = this->getProcesses().at(i - 1).getContext().getWaitingTime();
		this->processes.at(i).setWaitingTime(
			previousDurationTime + previousWaitingTime);
		int duration = this->getProcesses().at(i).getContext().getDuration();
		int waitingTime = this->getProcesses().at(i).getContext().getWaitingTime();
		this->processes.at(i).setTurnAroundTime(duration + waitingTime);
	}

	// Calculation of Waiting Times
	this->processes.at(0).setWaitingTime(0);
	for (size_t i = 1; i < this->getProcesses().size(); i++)
	{
		int previousDurationTime = this->getProcesses().at(i - 1).getContext().getDuration();
		int previousWaitingTime = this->getProcesses().at(i - 1).getContext().getWaitingTime();
		this->processes.at(i).setWaitingTime(
			previousDurationTime + previousWaitingTime);
	}

	// Find average time
	int totalWaitingTime = 0, totalTurnAroundTime = 0;
	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		totalWaitingTime = totalWaitingTime + this->getProcesses().at(i).getContext().getWaitingTime();
		totalTurnAroundTime = totalTurnAroundTime +
							  this->getProcesses().at(i).getContext().getTurnAroundTime();
	}

	// Calculation of Turn Around Time and printing the data.
	cout << "Average waiting time = "
		 << (float)totalWaitingTime / (float)this->getProcesses().size();
	cout << "\nAverage turn around time = "
		 << (float)totalTurnAroundTime / (float)this->getProcesses().size() << "\n";

	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		cout << this->getProcesses().at(i).getContext().getPid()
			 << " "
			 << this->getProcesses().at(i).getContext().getWaitingTime()
			 << " "
			 << this->getProcesses().at(i).getContext().getTurnAroundTime()
			 << "\n";
	}
	return 0;
}

int Scheduler::priorityWithoutPreemption()
{
	return 0;
}

int Scheduler::priorityWithPreemption()
{
	sort(this->processes.begin(), this->processes.end(), Scheduler::compareCreationTimes);

	int totalWaitingTime = 0, totalDurationTime = 0,
		insertedprocess = 0,
		totalResponseTime = 0;

	this->setCurrentTime(this->getProcesses().at(0).getContext().getCreationTime());

	// Calculating the total duration of the processes
	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		totalDurationTime += this->getProcesses().at(i).getContext().getDuration();
		this->processes.at(i).setDuration(this->getProcesses().at(i).getContext().getDuration());
	}

	// Inserting the processes in Heap according to creation time
	do
	{
		if (insertedprocess != (int)this->getProcesses().size())
		{
			for (size_t i = 0; i < this->getProcesses().size(); i++)
			{
				if (this->getProcesses().at(i).getContext().getCreationTime() == this->getCurrentTime())
				{
					++insertedprocess;
					this->getProcesses().at(i).setInTime(-1);
					this->getProcesses().at(i).setResponseTime(-1);
					this->insertProcessToHeap(this->getProcesses().at(i));
				}
			}
		}
		this->executeHighestPriorityFromHeap();
		this->setCurrentTime(this->getCurrentTime() + 1);

		if (this->getHeapSize() == 0 && insertedprocess == (int)this->getProcesses().size())
			break;
	} while (1);

	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		totalResponseTime += this->getProcesses().at(i).getContext().getResponseTime();
		totalWaitingTime += (this->getProcesses().at(i).getContext().getOutTime() - this->getProcesses().at(i).getContext().getInTime() - this->getProcesses().at(i).getContext().getDuration());
		totalDurationTime += this->getProcesses().at(i).getContext().getDuration();
	}

	printf("Average waiting time = %f\n",
		   ((float)totalWaitingTime / (float)this->getProcesses().size()));
	printf("Average response time =%f\n",
		   ((float)totalResponseTime / (float)this->getProcesses().size()));
	printf("Average turn around time = %f\n",
		   ((float)(totalWaitingTime + totalDurationTime) / (float)this->getProcesses().size()));
	return 0;
}

int Scheduler::roundRobin()
{
	//int contextSwitches = 0;
	int currentTime = 0;
	vector<Process> queue = this->getProcessesCreatedByTime(currentTime);

	// Time abstraction - every iteration here is the passage of one second
	Process currentProcess = queue.at(0);
	Process actualProcess = this->getProcessByPid(currentProcess.getPid());

	while (queue.size() > 0 && currentTime < 30)
	{
		bool isFinalPartOfQuantum = currentTime % 2 != 0;

		if (currentTime > 0)
		{
			vector<Process> createdProcesses = this->getProcessesCreatedByTime(currentTime);
			if (createdProcesses.size() > 0)
			{
				for (size_t i = 0; i < createdProcesses.size(); i++)
				{
					queue.push_back(createdProcesses.at(i));
				}
			}
		}

		// Getting first element only at beginning of quantums
		Process currentProcess = queue.at(0);
		Process actualProcess = this->getProcessByPid(currentProcess.getPid());

		cout << "Current pid: " << actualProcess.getPid() << endl;
		cout << "Executed time: " << actualProcess.context.executedTimeTotal << endl;

		actualProcess.context.executedTimeTotal++;

		int timeLeftToExecute = (actualProcess.getContext().getDuration()) - (actualProcess.getContext().getExecutedTimeTotal());
		cout << "  Time left: " << timeLeftToExecute << endl;
		printf("\n");

		if (timeLeftToExecute == 1)
		{
			printf("Vai acabar");
			// Means that process only has one second left to be done, and it won't be added at the end of the queue

			actualProcess.setDone();
			this->printRow(currentTime, actualProcess.getPid(), -1);
			// Only actually 'pop' if the process is done
			queue.erase(queue.begin());
		}
		else
		{
			// Means will need more than this second to be finished
			this->printRow(currentTime, actualProcess.getPid(), -1);
			//actualProcess.addExecutedTime(1);
			cout << "Executed time: " << actualProcess.context.executedTimeTotal << endl;

			if (isFinalPartOfQuantum)
			{
				// If this is the end of a quantum, this process will be sent back to the list
				queue.erase(queue.begin());
				queue.push_back(currentProcess);
			}
		}
		currentTime++;
	}

	return 0;
}

void Scheduler::insertProcess(Process _process)
{
	// TODO: change process status to "ready"
	this->processes.push_back(_process);
}

void Scheduler::insertProcessToHeap(Process _process)
{
	int start = this->getHeapSize();
	this->heap.insert(this->heap.begin(), _process);
	if (this->heap.at(this->getHeapSize()).getContext().getInTime() == -1)
	{
		this->heap.at(this->getHeapSize()).setInTime(this->getCurrentTime());
	}
	this->setHeapSize(this->getHeapSize() + 1);

	// Ordering the Heap
	while (start != 0 &&
		   this->heap.at((start - 1) / 2).getContext().getStaticPriority() > this->heap.at(start).getContext().getStaticPriority())
	{
		Process temp = this->heap.at((start - 1) / 2);
		this->heap.at((start - 1) / 2) = this->heap.at(start);
		this->heap.at(start) = temp;
		start = (start - 1) / 2;
	}
}

void Scheduler::orderHeap(int _start)
{
	int smallest = _start;
	int left = 2 * _start + 1;
	int right = 2 * _start + 2;

	if (left < this->getHeapSize() &&
		this->heap.at(left).getContext().getStaticPriority() < this->heap.at(smallest).getContext().getStaticPriority())
	{
		smallest = left;
	}

	if (right < this->getHeapSize() &&
		this->heap.at(left).getContext().getStaticPriority() < this->heap.at(smallest).getContext().getStaticPriority())
	{
		smallest = right;
	}

	// Ordering the Heap
	if (smallest != _start)
	{
		Process temp = this->heap.at(smallest);
		this->heap.at(smallest) = this->heap.at(smallest);
		this->heap.at(_start) = temp;
		this->orderHeap(smallest);
	}
}

Process Scheduler::extractminimum()
{
	Process min = this->heap.at(0);

	if (min.getContext().getResponseTime() == -1)
	{
		min.setResponseTime(this->getCurrentTime() - min.getContext().getCreationTime());
	}

	this->setHeapSize(this->getHeapSize() - 1);

	if (this->getHeapSize() >= 1)
	{
		this->heap.at(0) = this->heap.at(this->getHeapSize());
		this->orderHeap(0);
	}
	return min;
}

bool Scheduler::compareDurations(const Process &a, const Process &b)
{
	return a.getContextConst().getDuration() < b.getContextConst().getDuration();
}

bool Scheduler::compareCreationTimes(const Process &a, const Process &b)
{
	return a.getContextConst().getCreationTime() < b.getContextConst().getCreationTime();
}

void Scheduler::executeHighestPriorityFromHeap()
{
	if (this->getHeapSize() == 0)
		return;

	Process min = this->extractminimum();
	min.setOutTime(this->getCurrentTime() + 1);

	min.setDuration(min.getContext().getDuration() - 1);

	printf("[Executing] process id = %d current time = %d\n",
		   min.getPid(), this->getCurrentTime());

	// If the process is not yet finished insert it back into the Heap
	if (min.getContext().getDuration() > 0)
	{
		this->insertProcessToHeap(min);
		return;
	}

	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		if (this->getProcesses().at(i).getPid() == min.getPid())
		{
			this->getProcesses().at(i) = min;
			break;
		}
	}
}

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

// Used to convert any value to strings
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

/////////////// beautifiers ///////////////

void Scheduler::prettyPrint(
	string _statusp1, string _statusp2,
	string _statusp3, string _statusp4)
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

void Scheduler::printHeaders()
{
	string finalStr = "tempo";
	for (size_t i = 0; i < this->processes.size(); i++)
	{
		string currentIndex = to_string(i);
		finalStr.append(" P" + currentIndex);
	}
	finalStr.append("\n");

	cout << finalStr;
}

void Scheduler::printRow(
	int _currentTime, int _executingProcessPid, int _preemptedProcessPid)
{
	// Symbols
	const char *hashtag = "## ";
	const char *doubleDash = "-- ";
	const char *emptySpace = "   ";

	string currentTimeStr = to_string(_currentTime);
	string nextTickStr = to_string(_currentTime + 1);

	string finalStr = currentTimeStr + "- " + nextTickStr + "  ";

	for (size_t i = 0; i < this->processes.size(); i++)
	{
		int currentProcessPid = this->processes.at(i).getPid();
		Process currentProcess = this->processes.at(i);
		if (currentProcessPid == _executingProcessPid)
		{
			finalStr.append(hashtag);
		}
		else if (currentProcessPid == _preemptedProcessPid || currentProcess.getContext().getCurrentState() == "Ready")
		{
			finalStr.append(doubleDash);
		}
		else
		{
			finalStr.append(emptySpace);
		}
	}
	finalStr.append("\n");

	cout << finalStr;
}

/////////////// gets ///////////////

vector<ProcessParams *> Scheduler::getRawProcesses() { return this->rawProcesses; }
vector<Process> Scheduler::getProcesses() { return this->processes; }
vector<Process> Scheduler::getProcessesCreatedByTime(int _currentTime)
{
	vector<Process> createdProcesses;
	int size = this->getProcesses().size();
	for (int i = 0; i < size; i++)
	{
		Process currentProcess = this->processes.at(i);
		if (currentProcess.getContext().getCreationTime() == _currentTime)
		{
			createdProcesses.push_back(currentProcess);
		}
	}
	return createdProcesses;
}
Process Scheduler::getProcessByPid(pid_t _pid)
{
	if (!this->doesProcessExist(_pid))
	{
		printf("Process does not exist");
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
int Scheduler::getHeapSize() { return this->heapSize; }
int Scheduler::getCurrentTime() { return this->currentTime; }

/////////////// sets ///////////////

void Scheduler::setRawProcesses(vector<ProcessParams *> _rawProcesses)
{
	this->rawProcesses = _rawProcesses;
}
void Scheduler::setProcesses(vector<Process> _processes)
{
	this->processes = _processes;
}
void Scheduler::setAlgorithm(string _algorithm) { this->algorithm = _algorithm; }
void Scheduler::setHeapSize(int _heapSize) { this->heapSize = _heapSize; }
void Scheduler::setCurrentTime(int _currentTime) { this->currentTime = _currentTime; }
