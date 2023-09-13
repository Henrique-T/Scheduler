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
	Process();
	Process(int _creationTime, int _duration, int _priority);
	~Process();
	/**/
	pid_t getPid();
	/**/
	ContextProcess getContext() const;
	/**/
	void setPid(pid_t _pid);
	/**/
	void setContext(ContextProcess _context);
	/**/
	void setStartDate(int _startDate);
	/**/
	void setEndDate(int _endDate);
	/**/
	void setDuration(int _duration);
	/**/
	void setStaticPriority(int _staticPriority);
	/**/
	void setDynamicPriority(int _dynamicPriority);
	/**/
	void setCurrentState(string _currentState);
	/**/
	void setExecutedTimeCurrentQuantum(float _executedTimeCurrentQuantum);
	/**/
	void setExecutedTimeTotal(float _executedTimeTotal);
	/**/
	void setCreationTime(int _creationTime);
	/**/
	void setWaitingTime(int _waitingTime);
	/**/
	void setTurnAroundTime(int _turnAroundTime);
	/**/
	void setInTime(int _inTime);
	/**/
	void setOutTime(int _outTime);
	/**/
	void setResponseTime(int _responseTime);
};

#endif