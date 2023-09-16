#include "ContextProcess.h"
#include <cstdio>

ContextProcess::ContextProcess() {}

ContextProcess::ContextProcess(int _pid, int _creationTime, int _duration, int _priority)
{
	this->setPid(_pid);
	this->setCreationTime(_creationTime);
	this->setDuration(_duration);
	this->setStaticPriority(_priority);

	// Static attributes
	this->setDynamicPriority(0);
	this->setExecutedTimeTotal(0);
	this->setCurrentState("novo");
	this->setTurnAroundTime(0);
	this->setWaitingTime(0);

	// we might need more stuff here
}

ContextProcess::~ContextProcess() {}

/////////////// gets ///////////////

pid_t ContextProcess::getPid() { return this->pid; }
int ContextProcess::getStartDate() { return this->startDate; }
int ContextProcess::getEndDate() { return this->endDate; }
int ContextProcess::getDuration() const { return this->duration; }
int ContextProcess::getStaticPriority() const { return this->staticPriority; }
int ContextProcess::getDynamicPriority() { return this->dynamicPriority; }
string ContextProcess::getCurrentState() { return this->currentState; }
int ContextProcess::getExecutedTimeCurrentQuantum() { return this->executedTimeCurrentQuantum; }
int ContextProcess::getExecutedTimeTotal() { return this->executedTimeTotal; }
int ContextProcess::getCreationTime() { return this->creationTime; }
int ContextProcess::getWaitingTime() { return this->waitingTime; }
int ContextProcess::getTurnAroundTime() { return this->turnAroundTime; }
int ContextProcess::getInTime() { return this->inTime; }
int ContextProcess::getOutTime() { return this->outTime; }
int ContextProcess::getArrivalTime() { return this->arrivalTime; }
int ContextProcess::getResponseTime() { return this->responseTime; }

/////////////// sets ///////////////

void ContextProcess::setPid(pid_t _pid) { this->pid = _pid; }
void ContextProcess::setStartDate(int _startDate) { this->startDate = _startDate; }
void ContextProcess::setEndDate(int _endDate) { this->endDate = _endDate; }
void ContextProcess::setDuration(int _duration) { this->duration = _duration; }
void ContextProcess::setStaticPriority(int _staticPriority) { this->staticPriority = _staticPriority; }
void ContextProcess::setDynamicPriority(int _dynamicPriority) { this->dynamicPriority = _dynamicPriority; }
void ContextProcess::setCurrentState(string _currentState) { this->currentState = _currentState; }
void ContextProcess::setExecutedTimeCurrentQuantum(int _executedTimeCurrentQuantum) { this->executedTimeCurrentQuantum = _executedTimeCurrentQuantum; }
void ContextProcess::setExecutedTimeTotal(int _executedTimeTotal) { this->executedTimeTotal = _executedTimeTotal; }
void ContextProcess::addExecutedTime(int &_executedTime) { this->executedTimeTotal+= _executedTime; }
void ContextProcess::setCreationTime(int _creationTime) { this->creationTime = _creationTime; }
void ContextProcess::setWaitingTime(int _waitingTime) { this->waitingTime = _waitingTime; }
void ContextProcess::setTurnAroundTime(int _turnAroundTime) { this->turnAroundTime = _turnAroundTime; }
void ContextProcess::setInTime(int _inTime) { this->inTime = _inTime; }
void ContextProcess::setOutTime(int _outTime) { this->outTime = _outTime; }
void ContextProcess::setArrivalTime(int _arrivalTime) { this->arrivalTime = _arrivalTime; }
void ContextProcess::setResponseTime(int _responseTime) { this->arrivalTime = _responseTime; }