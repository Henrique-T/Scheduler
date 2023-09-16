#include "Scheduler.h"
#include "File.h"
#include <map>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

/* HELPER FUNCTIONS AREA */

// Used to convert any value to strings
template <typename T>
    std::string to_string(T value)
    {
      std::ostringstream os;
      os << value;
      return os.str();
    }

/* END OF HELPER FUNCTIONS AREA */

Scheduler::Scheduler() {}

Scheduler::Scheduler(string _algorithm)
{
	/* Read the file and create a list of processes of type Process. */
	File f;
	f.read_file();
	this->setRawProcesses(f.getProcesses());
	this->createProcesses();
	this->setAlgorithm(_algorithm);
	this->printHeaders();

	// for (size_t i = 0; i < this->getProcesses().size(); i++)
	// {
	// 	Process process = this->getProcesses().at(i);
	// 	cout << "creation time: " << process.getContext().getCreationTime() << "\n";
	// 	cout << "duration: " << process.getContext().getDuration() << "\n";
	// 	cout << "priority: " << process.getContext().getStaticPriority() << "\n";
	// 	cout << "--------------------------------------------------------"
	// 		 << "\n";
	// }

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
	// this is where we start everything. I'm aware the f.getProcesses() already gives us
	// a list of processes, but I want to move to our own list.
	// In here we create the processes.

	for (size_t i = 0; i < this->getRawProcesses().size(); i++)
	{
		ProcessParams *currentRawProcess = this->getRawProcesses().at(i);
		Process process(
			currentRawProcess->getCreationTime(),
			currentRawProcess->getDuration(),
			currentRawProcess->getPriority(),
			i);
		this->insertProcess(process);
	}
}

/////////////// Scheduling Algorithms and helpers ///////////////

bool Scheduler::compareProcessesByStaticPriorityAsc(const Process* a, const Process* b) {
    return a->getContext().getStaticPriority() > b->getContext().getStaticPriority();
}

bool Scheduler::compareProcessesByDurationDesc(const Process* a, const Process* b) {
    return a->getContext().getDuration() < b->getContext().getDuration();
}

int Scheduler::FCFS()
{
	int contextSwitches = 1;
	int currentTime = 0;
	std::vector<Process*> queue = this->getProcessesCreatedByTime(currentTime);
	for (size_t i = 0; i < queue.size(); i++) {
		Process* currentProcessLoop = queue.at(i);
		currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
	}

	// Tracker to check if the past executing process was finalized
	bool pastProcessFinished = false;

	// Time abstraction - every iteration here is the passage of one second
	while (queue.size() > 0)
	{
		if (currentTime > 0) {
			// If time is past 0, it means we always have to check if there are any new processes being created at this instant
			vector<Process *> createdProcesses = this->getProcessesCreatedByTime(currentTime);
			if (createdProcesses.size() > 0) {
				for (size_t i = 0; i < createdProcesses.size(); i++) {
					Process* currentProcessLoop = createdProcesses.at(i);
					currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
					queue.push_back(createdProcesses.at(i));
				}
			}
		}

		for (size_t i = 0; i < queue.size(); i++) {
			Process* currentProcessLoop = queue.at(i);
			// Increasing turn around time for all processes in queue
			currentProcessLoop->setTurnAroundTime(currentProcessLoop->getContext().getTurnAroundTime() + 1); 
			// Increasing waiting time for the rest of processes (excluding first process in the list, since it's the one executing)
			if (i != 0) {
				currentProcessLoop->setWaitingTime(currentProcessLoop->getContext().getWaitingTime() + 1);
			}
		}
		
		// We only 're-sort' queue after a process is done
		if (pastProcessFinished) {
			/* CONTEXT SWITCH !!! */
			contextSwitches++;
			pastProcessFinished = false;
		}

		Process* currentProcess = queue.at(0);
		// Avoiding setting executing more than once
		if (pastProcessFinished) {
			currentProcess->setCurrentState("Executing"); // Setting current process to executing
		}

		int timeLeftToExecute = (currentProcess->getContext().getDuration()) - (currentProcess->getContext().getExecutedTimeTotal());
		
		if (timeLeftToExecute == 1) {
			// Means that process only has one second left to be done, and it won't be added at the end of the queue
			int value = 1;
			currentProcess->addExecutedTime(value);
			currentProcess->setDone();
			pastProcessFinished = true;

			this->printRow(currentTime, currentProcess->getPid(), -1);
			// Only actually 'pop' if the process is done
			queue.erase(queue.begin());
			
		} else {
			// Means will need more than this second to be finished
			int value = 1;
			currentProcess->addExecutedTime(value);
			this->printRow(currentTime, currentProcess->getPid(), -1);
		}
		currentTime++;
	}
	// Also add up to the context switches number if the queue has finished
	contextSwitches++;
	this->printFinalStats(contextSwitches);

	return 0;
}

int Scheduler::shortestJobFirst()
{
	int contextSwitches = 1;
	int currentTime = 0;
	std::vector<Process*> queue = this->getProcessesCreatedByTime(currentTime);
	for (size_t i = 0; i < queue.size(); i++) {
		Process* currentProcessLoop = queue.at(i);
		currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
	}

	// Tracker to check if the past executing process was finalized
	bool pastProcessFinished = false;

	std::sort(queue.begin(), queue.end(), this->compareProcessesByDurationDesc);

	// Time abstraction - every iteration here is the passage of one second
	while (queue.size() > 0)
	{
		if (currentTime > 0) {
			// If time is past 0, it means we always have to check if there are any new processes being created at this instant
			vector<Process *> createdProcesses = this->getProcessesCreatedByTime(currentTime);
			if (createdProcesses.size() > 0) {
				for (size_t i = 0; i < createdProcesses.size(); i++) {
					Process* currentProcessLoop = createdProcesses.at(i);
					currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
					queue.push_back(createdProcesses.at(i));
				}
			}
		}

		for (size_t i = 0; i < queue.size(); i++) {
			Process* currentProcessLoop = queue.at(i);
			// Increasing turn around time for all processes in queue
			currentProcessLoop->setTurnAroundTime(currentProcessLoop->getContext().getTurnAroundTime() + 1); 
			// Increasing waiting time for the rest of processes (excluding first process in the list, since it's the one executing)
			if (i != 0) {
				currentProcessLoop->setWaitingTime(currentProcessLoop->getContext().getWaitingTime() + 1);
			}
		}
		
		// We only 're-sort' queue after a process is done
		if (pastProcessFinished) {
			/* CONTEXT SWITCH !!! */
			contextSwitches++;
			pastProcessFinished = false;	
			std::sort(queue.begin(), queue.end(), compareProcessesByDurationDesc);
		}

		Process* currentProcess = queue.at(0);
		// Avoiding setting executing more than once
		if (pastProcessFinished) {
			currentProcess->setCurrentState("Executing"); // Setting current process to executing
		}

		int timeLeftToExecute = (currentProcess->getContext().getDuration()) - (currentProcess->getContext().getExecutedTimeTotal());
		
		if (timeLeftToExecute == 1) {
			// Means that process only has one second left to be done, and it won't be added at the end of the queue
			int value = 1;
			currentProcess->addExecutedTime(value);
			currentProcess->setDone();
			pastProcessFinished = true;

			this->printRow(currentTime, currentProcess->getPid(), -1);
			// Only actually 'pop' if the process is done
			queue.erase(queue.begin());
			
		} else {
			// Means will need more than this second to be finished
			int value = 1;
			currentProcess->addExecutedTime(value);
			this->printRow(currentTime, currentProcess->getPid(), -1);
		}
		currentTime++;
	}
	// Also add up to the context switches number if the queue has finished
	contextSwitches++;
	this->printFinalStats(contextSwitches);

	return 0;
}

int Scheduler::priorityWithoutPreemption(/* args */)
{
	int contextSwitches = 1;
	int currentTime = 0;
	std::vector<Process*> queue = this->getProcessesCreatedByTime(currentTime);
	for (size_t i = 0; i < queue.size(); i++) {
		Process* currentProcessLoop = queue.at(i);
		currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
	}

	// Tracker to check if the past executing process was finalized
	bool pastProcessFinished = false;

	std::sort(queue.begin(), queue.end(), this->compareProcessesByStaticPriorityAsc);

	// Time abstraction - every iteration here is the passage of one second
	while (queue.size() > 0)
	{
		if (currentTime > 0) {
			// If time is past 0, it means we always have to check if there are any new processes being created at this instant
			vector<Process *> createdProcesses = this->getProcessesCreatedByTime(currentTime);
			if (createdProcesses.size() > 0) {
				for (size_t i = 0; i < createdProcesses.size(); i++) {
					Process* currentProcessLoop = createdProcesses.at(i);
					currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
					queue.push_back(createdProcesses.at(i));
				}
			}
		}

		for (size_t i = 0; i < queue.size(); i++) {
			Process* currentProcessLoop = queue.at(i);
			// Increasing turn around time for all processes in queue
			currentProcessLoop->setTurnAroundTime(currentProcessLoop->getContext().getTurnAroundTime() + 1); 
			// Increasing waiting time for the rest of processes (excluding first process in the list, since it's the one executing)
			if (i != 0) {
				currentProcessLoop->setWaitingTime(currentProcessLoop->getContext().getWaitingTime() + 1);
			}
		}
		
		// We only 're-sort' queue after a process is done
		if (pastProcessFinished) {
			/* CONTEXT SWITCH !!! */
			contextSwitches++;
			pastProcessFinished = false;	
			std::sort(queue.begin(), queue.end(), this->compareProcessesByStaticPriorityAsc);
		}

		Process* currentProcess = queue.at(0);
		// Avoiding setting executing more than once
		if (pastProcessFinished) {
			currentProcess->setCurrentState("Executing"); // Setting current process to executing
		}

		int timeLeftToExecute = (currentProcess->getContext().getDuration()) - (currentProcess->getContext().getExecutedTimeTotal());
		
		if (timeLeftToExecute == 1) {
			// Means that process only has one second left to be done, and it won't be added at the end of the queue
			int value = 1;
			currentProcess->addExecutedTime(value);
			currentProcess->setDone();
			pastProcessFinished = true;

			this->printRow(currentTime, currentProcess->getPid(), -1);
			// Only actually 'pop' if the process is done
			queue.erase(queue.begin());
			
		} else {
			// Means will need more than this second to be finished
			int value = 1;
			currentProcess->addExecutedTime(value);
			this->printRow(currentTime, currentProcess->getPid(), -1);
		}
		currentTime++;
	}
	// Also add up to the context switches number if the queue has finished
	contextSwitches++;
	this->printFinalStats(contextSwitches);

	return 0;
}

int Scheduler::priorityWithPreemption(/* args */)
{
	int contextSwitches = 1;
	int currentTime = 0;
	std::vector<Process*> queue = this->getProcessesCreatedByTime(currentTime);

	for (size_t i = 0; i < queue.size(); i++) {
		Process* currentProcessLoop = queue.at(i);
		currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
	}

	int executingPid;

	// Time abstraction - every iteration here is the passage of one second
	while (queue.size() > 0)
	{
		if (currentTime > 0) {
			// If time is past 0, it means we always have to check if there are any new processes being created at this instant
			vector<Process *> createdProcesses = this->getProcessesCreatedByTime(currentTime);
			if (createdProcesses.size() > 0) {
				for (size_t i = 0; i < createdProcesses.size(); i++) {
					Process* currentProcessLoop = createdProcesses.at(i);
					currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
					queue.push_back(createdProcesses.at(i));
				}
			}
		}

		std::sort(queue.begin(), queue.end(), this->compareProcessesByStaticPriorityAsc);

		for (size_t i = 0; i < queue.size(); i++) {
			Process* currentProcessLoop = queue.at(i);
			// Increasing turn around time for all processes in queue
			currentProcessLoop->setTurnAroundTime(currentProcessLoop->getContext().getTurnAroundTime() + 1); 
			// Increasing waiting time for the rest of processes (excluding first process in the list, since it's the one executing)
			if (i != 0) {
				currentProcessLoop->setWaitingTime(currentProcessLoop->getContext().getWaitingTime() + 1);
			}
		}
		
		// We always get the first element of the queue
		Process* currentProcess = queue.at(0);

		if (currentTime == 0) {
			executingPid = currentProcess->getPid();
		}

		// If the past executing process is different than the upcoming one, it means that there were a context switch
		if (currentProcess->getPid() != executingPid) {
			/* CONTEXT SWITCH !!! */
			contextSwitches++;
		}
		
		executingPid = currentProcess->getPid();
		
		currentProcess->setCurrentState("Executing"); // Setting current process to executing
		
		int timeLeftToExecute = (currentProcess->getContext().getDuration()) - (currentProcess->getContext().getExecutedTimeTotal());
		
		if (timeLeftToExecute == 1) {
			// Means that process only has one second left to be done, and it won't be added at the end of the queue
			int value = 1;
			currentProcess->addExecutedTime(value);
			currentProcess->setDone();
			this->printRow(currentTime, currentProcess->getPid(), -1);
			// Only actually 'pop' if the process is done
			queue.erase(queue.begin());
			
		} else {
			// Means will need more than this second to be finished
			int value = 1;
			currentProcess->addExecutedTime(value);
			this->printRow(currentTime, currentProcess->getPid(), -1);
			currentProcess->setCurrentState("Ready");
		}
		currentTime++;
	}
	// Also add up to the context switches number if the queue has finished
	contextSwitches++;
	this->printFinalStats(contextSwitches);

	return 0;
}

int Scheduler::roundRobin()
{
	int contextSwitches = 1;
	int currentTime = 0;
	std::vector<Process*> queue = this->getProcessesCreatedByTime(currentTime);
	for (size_t i = 0; i < queue.size(); i++) {
		Process* currentProcessLoop = queue.at(i);
		currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
	}

	// Time abstraction - every iteration here is the passage of one second
	while (queue.size() > 0)
	{
		bool isFinalPartOfQuantum = currentTime % 2 != 0;

		if (currentTime > 0) {
			// If time is past 0, it means we have to check if there are any new processes being created at this instant
			vector<Process *> createdProcesses = this->getProcessesCreatedByTime(currentTime);
			if (createdProcesses.size() > 0) {
				for (size_t i = 0; i < createdProcesses.size(); i++) {
					Process* currentProcessLoop = createdProcesses.at(i);
					currentProcessLoop->setCurrentState("Ready"); // Setting scheduled process to ready
					queue.push_back(createdProcesses.at(i));
				}
			}
		}

		for (size_t i = 0; i < queue.size(); i++) {
			Process* currentProcessLoop = queue.at(i);
			// Increasing turn around time for all processes in queue
			currentProcessLoop->setTurnAroundTime(currentProcessLoop->getContext().getTurnAroundTime() + 1); 
			// Increasing waiting time for the rest of processes (excluding first process in the list, since it's the one executing)
			if (i != 0) {
				currentProcessLoop->setWaitingTime(currentProcessLoop->getContext().getWaitingTime() + 1);
			}
		}
		
		// We always get the first element of the queue
		Process* currentProcess = queue.at(0);
		currentProcess->setCurrentState("Executing"); // Setting current process to executing

		int timeLeftToExecute = (currentProcess->getContext().getDuration()) - (currentProcess->getContext().getExecutedTimeTotal());
		
		if (timeLeftToExecute == 1) {
			// Means that process only has one second left to be done, and it won't be added at the end of the queue
			int value = 1;
			currentProcess->addExecutedTime(value);
			currentProcess->setDone();
			this->printRow(currentTime, currentProcess->getPid(), -1);

			// Only actually 'pop' if the process is done
			queue.erase(queue.begin());

			/* CONTEXT SWITCH !!! */
			contextSwitches++;
		} else {
			// Means will need more than this second to be finished
			int value = 1;
			currentProcess->addExecutedTime(value);
			this->printRow(currentTime, currentProcess->getPid(), -1);
			
			if (isFinalPartOfQuantum) {
				// If this is the end of a quantum, this process will be sent back to the list
				currentProcess->setCurrentState("Ready");
				queue.erase(queue.begin());
				queue.push_back(currentProcess);
				/* CONTEXT SWITCH !!! */
				contextSwitches++;
			}
		}
		currentTime++;
	}
	// We don't need to do the final context switch addition because the above check for FinalQuantums already covers it
	this->printFinalStats(contextSwitches);

	return 0;
}

void Scheduler::findTurnAroundTimeForEach() {}
void Scheduler::findWaitingTimeForEach() {}
void Scheduler::findTotalTimesOfContextChangeForEach() {}
void Scheduler::findAverageTurnAroundTime() {}
void Scheduler::findAverageWaitingTime() {}
void Scheduler::findAverageTimesOfContextChange() {}

/////////////// gets ///////////////

vector<ProcessParams *> Scheduler::getRawProcesses() { return this->rawProcesses; }

vector<Process> Scheduler::getProcesses() { return this->processes; }

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

std::vector<Process*> Scheduler::getProcessesCreatedByTime(int _currentTime)
{
	std::vector<Process*> createdProcesses;
    for (size_t i = 0; i < this->processes.size(); i++) {
        Process* currentProcess = &this->processes.at(i);
        if (currentProcess->getContext().getCreationTime() == _currentTime) {
            createdProcesses.push_back(currentProcess);
        }
    }
    return createdProcesses;
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
	// for (size_t i = 0; i < _processes.size(); i++)
	// {
	// 	this->processes.push_back(_processes[i]);
	// }
}

void Scheduler::setAlgorithm(string _algorithm) { this->algorithm = _algorithm; }
void Scheduler::setHeapSize(int _heapSize) { this->heapSize = _heapSize; }
void Scheduler::setCurrentTime(int _currentTime) { this->currentTime = _currentTime; }

void Scheduler::insertProcess(Process _process)
{
	this->processes.push_back(_process);
}

void Scheduler::insertProcessToHeap(Process _process)
{
	int start = this->getHeapSize(), i;
	this->heap.at(this->getHeapSize()) = _process;

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
	// Process min = Heap[0];
	Process min = this->heap.at(0);
	if (min.getContext().getResponseTime() == -1)
	{
		min.setResponseTime(this->getCurrentTime() - min.getContext().getArrivalTime());
	}
	this->setHeapSize(this->getHeapSize() - 1);
	if (this->getHeapSize() >= 1)
	{
		this->heap.at(0) = this->heap.at(this->getHeapSize());
		this->orderHeap(0);
	}
	return min;
}

/////////////// beautifiers ///////////////

void Scheduler::printFinalStats(int _numberofContextSwitches)
{
	string finalStr = "\n--x-- ESTATÍSTICAS FINAIS --x--\n\n";
	for (size_t i = 0; i < this->processes.size(); i++)
	{
		Process currentProcess = this->processes.at(i);
		finalStr.append("P" + to_string(currentProcess.getPid()) + " teve como turn around time: " + to_string(currentProcess.getContext().getTurnAroundTime()) + " segundos.\n");
	}
	finalStr.append("\n");

	int totalTurnAroundTime = 0;
	int totalWaitingTime = 0;

	// Find average times
	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		totalTurnAroundTime = totalTurnAroundTime + this->getProcesses().at(i).getContext().getTurnAroundTime();
		totalWaitingTime = totalWaitingTime + this->getProcesses().at(i).getContext().getWaitingTime();
	}
	float averageTurnAroundTime = round(totalTurnAroundTime / this->getProcesses().size());
	float averageWaitingTime = round(totalWaitingTime / this->getProcesses().size());

	finalStr.append("Turn around médio: " + to_string(averageTurnAroundTime) + "\n");
	finalStr.append("Tempo de espera médio: " + to_string(averageWaitingTime) + "\n");
	finalStr.append("Número de trocas de contexto: " + to_string(_numberofContextSwitches) + "\n");
	
	cout << finalStr;
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
	int _currentTime, int _executingProcessPid, int _preemptedProcessPid
)
{
	// Symbols
	const char *hashtag = "## ";
	const char *doubleDash = "-- ";
	const char *emptySpace = "   ";

	string currentTimeStr = to_string(_currentTime);
	string nextTickStr = to_string(_currentTime + 1);

	string finalStr = currentTimeStr + "- " + nextTickStr + "  ";

	// Adjusting print for bigger time stamps
	if (currentTimeStr.size() > 1 && nextTickStr.size() > 1) {
		finalStr = currentTimeStr + "-" + nextTickStr + " ";
	}

	else if (currentTimeStr.size() <= 1 && nextTickStr.size() > 1) {
		finalStr = currentTimeStr + "- " + nextTickStr + " ";
	}

	// Looping through all processes and checking their states
	for (size_t i = 0; i < this->processes.size(); i++)
	{
		int currentProcessPid = this->processes.at(i).getPid();
		Process currentProcess = this->processes.at(i);
		if (currentProcessPid == _executingProcessPid) {
			finalStr.append(hashtag);
		} else if (currentProcessPid == _preemptedProcessPid || currentProcess.getContext().getCurrentState() == "Ready") {
			finalStr.append(doubleDash);
		} else {
			finalStr.append(emptySpace);
		}
	}
	finalStr.append("\n");
	
	cout << finalStr;
}

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