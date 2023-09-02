#include "Process.h"
#include "ContextProcess.h"
#include <cstdlib>

Process::Process(int _creationTime, int _duration, int _priority)
{
	// create and set pid (within range 0-10);
	int range = 10;
	this->setPid(rand() % range);

	// create and set context
	ContextProcess context(this->getPid(), _creationTime, _duration, _priority);
	this->setContext(context);
}

Process::~Process() {}

// gets
pid_t Process::getPid() { return this->pid; }
ContextProcess Process::getContext() { return this->context; }

// sets
void Process::setPid(pid_t _pid) { this->pid = _pid; }
void Process::setContext(ContextProcess _context) { this->context = _context; }