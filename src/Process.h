#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include "ContextProcess.h"

/*
	Represents a process.
*/
class Process
{
public:
	Process(int _creatioTime, int _duration, int _priority);
	~Process();

private:
	/* data */
	pid_t pid;
	ContextProcess context;
};

#endif