#include "ContextProcess.h"
#include <cstdlib>

ContextProcess::ContextProcess() {}

ContextProcess::ContextProcess(int _pid, int _creationTime, int _duration, int _priority)
{
	this->setPid(_pid);
	this->setCreationTime(_creationTime);
	this->setDuration(_duration);
	this->setStaticPriority(_priority);
	this->setCurrentState("novo");
	this->setArrivalTime(rand() % 20);
	// this->setTurnAroundTime(0);
	// this->setWaitingTime(0);

	// we might need more stuff here
}

ContextProcess::~ContextProcess() {}

/////////////// gets ///////////////

pid_t ContextProcess::getPid() { return this->pid; }
int ContextProcess::getStartDate() { return this->startDate; }
int ContextProcess::getEndDate() { return this->endDate; }
int ContextProcess::getDuration() const { return this->duration; }
int ContextProcess::getStaticPriority() { return this->staticPriority; }
int ContextProcess::getDynamicPriority() { return this->dynamicPriority; }
string ContextProcess::getCurrentState() { return this->currentState; }
float ContextProcess::getExecutedTimeCurrentQuantum() { return this->executedTimeCurrentQuantum; }
float ContextProcess::getExecutedTimeTotal() { return this->executedTimeTotal; }
int ContextProcess::getCreationTime() { return this->creationTime; }
int ContextProcess::getWaitingTime() { return this->waitingTime; }
int ContextProcess::getTurnAroundTime() { return this->turnAroundTime; }
int ContextProcess::getInTime() { return this->inTime; }
int ContextProcess::getOutTime() { return this->outTime; }
int ContextProcess::getArrivalTime() { return this->arrivalTime; }
int ContextProcess::getResponseTime() { return this->responseTime; }
int ContextProcess::getAuxDuration() { return this->auxDuration; }

/////////////// sets ///////////////

void ContextProcess::setPid(pid_t _pid) { this->pid = _pid; }
void ContextProcess::setStartDate(int _startDate) { this->startDate = _startDate; }
void ContextProcess::setEndDate(int _endDate) { this->endDate = _endDate; }
void ContextProcess::setDuration(int _duration) { this->duration = _duration; }
void ContextProcess::setStaticPriority(int _staticPriority) { this->staticPriority = _staticPriority; }
void ContextProcess::setDynamicPriority(int _dynamicPriority) { this->dynamicPriority = _dynamicPriority; }
void ContextProcess::setCurrentState(string _currentState) { this->currentState = _currentState; }
void ContextProcess::setExecutedTimeCurrentQuantum(float _executedTimeCurrentQuantum) { this->executedTimeCurrentQuantum = _executedTimeCurrentQuantum; }
void ContextProcess::setExecutedTimeTotal(float _executedTimeTotal) { this->executedTimeTotal = _executedTimeTotal; }
void ContextProcess::setCreationTime(int _creationTime) { this->creationTime = _creationTime; }
void ContextProcess::setWaitingTime(int _waitingTime) { this->waitingTime = _waitingTime; }
void ContextProcess::setTurnAroundTime(int _turnAroundTime) { this->turnAroundTime = _turnAroundTime; }
void ContextProcess::setInTime(int _inTime) { this->inTime = _inTime; }
void ContextProcess::setOutTime(int _outTime) { this->outTime = _outTime; }
void ContextProcess::setArrivalTime(int _arrivalTime) { this->arrivalTime = _arrivalTime; }
void ContextProcess::setResponseTime(int _responseTime) { this->arrivalTime = _responseTime; }
void ContextProcess::setAuxDuration(int _auxDuration) { this->auxDuration = _auxDuration; }