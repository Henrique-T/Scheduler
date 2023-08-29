#ifndef CONTEXT_PROCESS_H
#define CONTEXT_PROCESS_H

#include <sys/types.h>
#include <string>
using namespace std;

/*
	Represents the context of a process.
*/
class ContextProcess
{
private:
	/* data */
	pid_t pid;
	int startDate;
	int endDate;
	float duration;
	int staticPriority;
	int dynamicPriority;
	string currentState;
	float executedTimeCurrentQuantum;
	float executedTimeTotal;

public:
	ContextProcess(/* args */);
	~ContextProcess();
};

#endif