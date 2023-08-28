#ifndef INE5412_H
#define INE5412_H

#include <sys/types.h>
#include "contextProcess.h"
#include "process.h"
#include "contextCPU.h"
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
	vector<process> createProcesses(vector<processParams *> _processes);

private:
	/* data */
	contextCPU contextCPU; // do we need a context for CPU?
};

#endif