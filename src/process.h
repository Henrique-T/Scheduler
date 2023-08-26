#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>
#include "contextProcess.h"

/*
	Represents a process.
*/
class process
{
public:
	process(/* args */);
	~process();

private:
	/* data */
	pid_t pid;
	contextProcess context;
};

#endif