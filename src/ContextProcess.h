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
	int duration;
	int staticPriority;
	int dynamicPriority;
	string currentState; // new, ready, executing, done
	float executedTimeCurrentQuantum;
	float executedTimeTotal;
	int creationTime;
	int waitingTime;
	int turnAroundTime;

public:
	ContextProcess();
	ContextProcess(int _pid, int _creationTime, int _duration, int _priority);
	~ContextProcess();

	pid_t getPid();
	/**/
	int getStartDate();
	/**/
	int getEndDate();
	/**/
	int getDuration();
	/**/
	int getStaticPriority();
	/**/
	int getDynamicPriority();
	/**/
	string getCurrentState();
	/**/
	float getExecutedTimeCurrentQuantum();
	/**/
	float getExecutedTimeTotal();
	/**/
	int getCreationTime();
	/**/
	int getWaitingTime();
	/**/
	int getTurnAroundTime();
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
	void setExecutedTimeCurrentQuantum(float _executedTimeCurrentQuantum);
	/**/
	void setExecutedTimeTotal(float _executedTimeTotal);
	/**/
	void setCreationTime(int _creationTime);
	/**/
	void setWaitingTime(int _waitingTime);
	/**/
	void setTurnAroundTime(int _turnAroundTime);
};

#endif