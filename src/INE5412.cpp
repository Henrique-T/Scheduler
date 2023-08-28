#include "INE5412.h"
#include "processParams.h"
#include "file.h"
#include "scheduler.h"

INE5412::INE5412(/* args */)
{
	// Read the file and create a list of processes of type process.
	file f;
	f.read_file();
	vector<processParams *> rawProcesses = f.getProcesses();
	vector<process> processes = this->createProcesses(rawProcesses);

	// Create and call scheduler.
	scheduler *sched = new scheduler::scheduler(processes, "");
}

INE5412::~INE5412()
{
}

vector<process> createProcesses(vector<processParams *> _processes)
{
	// this is where we start everything. I'm aware the f.getProcesses() already gives us
	// a list of processes, but I want to move to our own list.
	// In here we create the processes, set their context...
}

// int main()
// {
// 	File f;
// 	f.read_file();
// 	f.print_processes_params();
// }