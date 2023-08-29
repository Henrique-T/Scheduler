#ifndef INE5412_H
#define INE5412_H

#include <sys/types.h>
#include "ContextProcess.h"
#include "Process.h"
#include "ContextCPU.h"
#include "processParams.h"
#include <vector>

using namespace std;

/*
	Entry point.
	Uses processParams to read file, create processes and call scheduler.
*/
class INE5412
{
public:
	INE5412(/* args */);
	~INE5412();
	vector<Process> createProcesses(vector<ProcessParams *> _processes, int _qtyOfRawProcesses);

private:
	/* data */
	ContextCPU _contextCPU; // do we need a context for CPU?
};

#endif