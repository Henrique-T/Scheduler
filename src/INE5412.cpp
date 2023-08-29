#include "INE5412.h"
#include "processParams.h"
#include "File.h"
#include "Scheduler.h"

using namespace std;

INE5412::INE5412(/* args */)
{
	// Read the file and create a list of processes of type process.
	File f;
	f.read_file();
	vector<ProcessParams *> rawProcesses = f.getProcesses();
	vector<Process> processes = this->createProcesses(rawProcesses, rawProcesses.size());

	// Create and call scheduler.
	// scheduler *sched = new scheduler::scheduler(processes, "");
}

INE5412::~INE5412()
{
}

vector<Process> createProcesses(vector<ProcessParams *> _rawProcesses, int _qtyOfRawProcesses)
{
	// this is where we start everything. I'm aware the f.getProcesses() already gives us
	// a list of processes, but I want to move to our own list.
	// In here we create the processes and return a list of them.
	vector<Process> processes;
	for (int i = 0; i < _qtyOfRawProcesses; i++)
	{
		ProcessParams *currentRawProcess = _rawProcesses.at(i);
		Process process(
			currentRawProcess->getCreationTime(),
			currentRawProcess->getDuration(),
			currentRawProcess->getPriority());
		processes.push_back(process);
	}
	return processes;
}

// int main()
// {
// 	File f;
// 	f.read_file();
// 	f.print_processes_params();
// }