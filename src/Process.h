#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include "ContextProcess.h"

/*
	Represents a process.
*/
class Process
{
private:
	/* data */
	pid_t pid;
	ContextProcess context;

public:
	Process(int _creatioTime, int _duration, int _priority);
	~Process();

	// gets
	pid_t getPid();
	ContextProcess getContext();

	// sets
	void setPid(pid_t _pid);
	void setContext(ContextProcess _context);
};

#endif