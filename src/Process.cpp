#include "Process.h"
#include "ContextProcess.h"
#include <cstdlib>

Process::Process() {}

Process::Process(int _creationTime, int _duration, int _priority)
{
	// create and set pid (within range 0-20);
	int range = 20;
	this->setPid(rand() % range);

	// create and set context
	ContextProcess context(this->getPid(), _creationTime, _duration, _priority);
	this->setContext(context);
}

Process::~Process() {}

/////////////// gets ///////////////

pid_t Process::getPid() { return this->pid; }
ContextProcess Process::getContext() const { return this->context; }

/////////////// sets  ///////////////

void Process::setPid(pid_t _pid) { this->pid = _pid; }
void Process::setContext(ContextProcess _context) { this->context = _context; }
void Process::setStartDate(int _startDate) { this->context.setStartDate(_startDate); }
void Process::setEndDate(int _endDate) { this->context.setEndDate(_endDate); }
void Process::setDuration(int _duration) { this->context.setDuration(_duration); }
void Process::setStaticPriority(int _staticPriority) { this->context.setStaticPriority(_staticPriority); }
void Process::setDynamicPriority(int _dynamicPriority) { this->context.setDynamicPriority(_dynamicPriority); }
void Process::setCurrentState(string _currentState) { this->context.setCurrentState(_currentState); }
void Process::setExecutedTimeCurrentQuantum(float _executedTimeCurrentQuantum) { this->context.setExecutedTimeCurrentQuantum(_executedTimeCurrentQuantum); }
void Process::setExecutedTimeTotal(float _executedTimeTotal) { this->context.setExecutedTimeTotal(_executedTimeTotal); }
void Process::setCreationTime(int _creationTime) { this->context.setCreationTime(_creationTime); }
void Process::setWaitingTime(int _waitingTime) { this->context.setWaitingTime(_waitingTime); }
void Process::setTurnAroundTime(int _turnAroundTime) { this->context.setTurnAroundTime(_turnAroundTime); }
void Process::setInTime(int _inTime) { this->context.setInTime(_inTime); }
void Process::setOutTime(int _outTime) { this->context.setOutTime(_outTime); }
void Process::setResponseTime(int _responseTime) { this->context.setResponseTime(_responseTime); }