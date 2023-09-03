#include "INE5412.h"
#include "ProcessParams.h"
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

	for (size_t i = 0; i < processes.size(); i++)
	{
		Process current = processes.at(i);
		cout << "index: " << i << " pid: " << current.getPid() << "\n";
		cout << "state: " << current.getContext().getCurrentState() << "\n";
		cout << "---------------------------\n";
	}

	//Create and call scheduler.
	Scheduler sched;
	sched.prettyPrint(
		processes.at(0).getContext().getCurrentState(),
		processes.at(1).getContext().getCurrentState(),
		processes.at(2).getContext().getCurrentState(),
		processes.at(3).getContext().getCurrentState());
}

INE5412::~INE5412()
{
}

vector<Process> INE5412::createProcesses(vector<ProcessParams *> _rawProcesses, int _qtyOfRawProcesses)
{
	// this is where we start everything. I'm aware the f.getProcesses() already gives us
	// a list of processes, but I want to move to our own list.
	// In here we create the processes and return a list of them.

	// vector<ProcessParams *>::iterator iter = _rawProcesses.begin();
	// for (iter; iter < _rawProcesses.end(); iter++)
	// {
	// 	ProcessParams *p = *iter;
	// 	cout << *p;
	// }

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
