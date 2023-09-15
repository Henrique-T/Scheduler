#include "Scheduler.h"
#include "File.h"
#include <map>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

// Used to convert any value to strings
template <typename T>
    std::string to_string(T value)
    {
      std::ostringstream os ;
      os << value ;
      return os.str() ;
    }

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
			currentRawProcess->getPriority());
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

	// // Find average time
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

bool Scheduler::compareDurations(const Process &a, const Process &b)
{
	return a.getContext().getDuration() < b.getContext().getDuration();
}

bool compareArrivalTimes(const Process &a, const Process &b)
{
	return a.getContext().getArrivalTime() < b.getContext().getArrivalTime();
}

void Scheduler::executeHighestPriorityFromHeap()
{
	if (this->getHeapSize() == 0)
		return;

	Process min = this->extractminimum();
	min.setOutTime(this->getCurrentTime() + 1);
	min.setDuration(min.getContext().getDuration() - 1);
	printf("process id = %d current time = %d\n",
		   min.getPid(), this->getCurrentTime());

	// If the process is not yet finished
	// insert it back into the Heap*/
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

void Scheduler::manage()
{
	sort(array, array + n, compare);

	int totalwaitingtime = 0, totalbursttime = 0,
		totalturnaroundtime = 0, i, insertedprocess = 0,
		heapsize = 0, currentTime = array[0].arrivalTime,
		totalresponsetime = 0;

	Process Heap[4 * n];

	// Calculating the total burst time
	// of the processes
	for (int i = 0; i < n; i++)
	{
		totalbursttime += array[i].burstTime;
		array[i].tempburstTime = array[i].burstTime;
	}

	// Inserting the processes in Heap
	// according to arrival time
	do
	{
		if (insertedprocess != n)
		{
			for (i = 0; i < n; i++)
			{
				if (array[i].arrivalTime == currentTime)
				{
					++insertedprocess;
					array[i].intime = -1;
					array[i].responsetime = -1;
					insert(Heap, array[i],
						   &heapsize, ¤tTime);
				}
			}
		}
		scheduling(Heap, array, n,
				   &heapsize, ¤tTime);
		++currentTime;
		if (heapsize == 0 && insertedprocess == n)
			break;
	} while (1);

	for (int i = 0; i < n; i++)
	{
		totalresponsetime += array[i].responsetime;
		totalwaitingtime += (array[i].outtime - array[i].intime - array[i].tempburstTime);
		totalbursttime += array[i].burstTime;
	}
	printf("Average waiting time = %f\n",
		   ((float)totalwaitingtime / (float)n));
	printf("Average response time =%f\n",
		   ((float)totalresponsetime / (float)n));
	printf("Average turn around time = %f\n",
		   ((float)(totalwaitingtime + totalbursttime) / (float)n));
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
	// All tasks take their set turn around time  to finish
	// Total turn around time is calculated by the sum of all processes turn around time % 2 (since quantum = 2s)
	// So each iteration will count as one quantum, and consume 2s out of the first process(es) in queue
	int contextSwitches = 0;
	int totalDurationTime =  0;
	Process dummyProcess = Process();

	// Since there is no priority, the base queue will be the same as the associated list of processes
	vector<Process> queue;

	for (size_t i = 0; i < this->getProcesses().size(); i++)
	{
		queue.push_back(this->getProcesses().at(i)); // Adds process to queue
		totalDurationTime = totalDurationTime +
							  this->getProcesses().at(i).getContext().getDuration();
	}
	totalDurationTime = totalDurationTime / 2 + (totalDurationTime % 2 != 0);

	for (int i = 0; i < totalDurationTime; i++)
	{
		// Popping first element
		Process currentProcess = queue.front();
		queue.erase(queue.begin());
		// These are copies of processes, meaning we can manipulate their values 

		int timeLeftToExecute = currentProcess.getContext().getDuration() - currentProcess.getContext().getExecutedTimeTotal();
		Process actualProcess = this->getProcessByPid(currentProcess.getPid());
		
		if (timeLeftToExecute > 2) {
			// If time left is bigger than quantum, this process will consume the entire quantum by itself, 
			// and will return to the end of the queue
			currentProcess.setExecutedTimeTotal(currentProcess.getContext().getExecutedTimeTotal() + 2);
			this->printRow(i, actualProcess, dummyProcess);
			this->printRow(i + 1, actualProcess, dummyProcess);
			queue.push_back(currentProcess);

		} else if (timeLeftToExecute == 2) {
			// If time left to execute is exactly two, the process will also consume the entire quantum, and will be set to done
			this->printRow(i, currentProcess);
			this->printRow(i + 1, currentProcess, dummyProcess);
			actualProcess.setDone();
		} else {
			// If time left to execute is less than two, the process consume one quantum and the next process will consume the other one
			this->printRow(i, currentProcess, dummyProcess);
			actualProcess.setDone();

			// Gets the next process in line
			Process nextProcess = queue.front();
			queue.erase(queue.begin());

			int timeLeftToExecuteNextProcess = nextProcess.getContext().getDuration() - nextProcess.getContext().getExecutedTimeTotal();

			if (timeLeftToExecute == 1) {
				this->printRow(i + 1, nextProcess, dummyProcess);
				this->getProcessByPid(nextProcess.getPid()).setDone();
			} else {
				nextProcess.setExecutedTimeTotal(nextProcess.getContext().getExecutedTimeTotal() + 1);
				queue.push_back(nextProcess);
				this->printRow(i + 1, nextProcess, dummyProcess);
			}
		}		
	}

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
	int _currentTime, Process executingProcess, Process preemptedProcess
)
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
		if (currentProcessPid == executingProcess.getPid()) {
			finalStr.append(hashtag);
		} else if (currentProcessPid == preemptedProcess.getPid() || currentProcess.getContext().getCurrentState() == "Ready") {
			finalStr.append(doubleDash);
		} else {
			finalStr.append(emptySpace);
			// Process currentProcess = this->processes.at(i);
			// if (currentProcess.getContext().getCurrentState() == "DONE") {
			// 	finalStr.append(emptySpace);
			// }
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