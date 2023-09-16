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
	pid_t pid;
	int startDate;
	int endDate;
	int duration;
	int staticPriority;
	int dynamicPriority;
	string currentState; // new, ready, executing, done
	int executedTimeCurrentQuantum;
	int creationTime;
	int waitingTime;
	int turnAroundTime;
	int inTime;
	int outTime;
	int responseTime;

public:
	ContextProcess();
	ContextProcess(int _pid, int _creationTime, int _duration, int _priority);
	~ContextProcess();
	int executedTimeTotal;
	pid_t getPid();
	/**/
	int getStartDate();
	/**/
	int getEndDate();
	/**/
	int getDuration() const;
	/**/
	int getStaticPriority();
	/**/
	int getDynamicPriority();
	/**/
	string getCurrentState();
	/**/
	int getExecutedTimeCurrentQuantum();
	/**/
	int getExecutedTimeTotal();
	/**/
	int getCreationTime();
	/**/
	int getWaitingTime();
	/**/
	int getTurnAroundTime();
	/**/
	int getInTime();
	/**/
	int getOutTime();
	/**/
	int getResponseTime();
	/**/
	void setPid(pid_t _pid);
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
	void setExecutedTimeCurrentQuantum(int _executedTimeCurrentQuantum);
	/**/
	void setExecutedTimeTotal(int _executedTimeTotal);
	/**/
	void addExecutedTime(int &_executedTime);
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