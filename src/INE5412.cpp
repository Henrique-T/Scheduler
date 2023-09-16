#include "INE5412.h"
#include "ProcessParams.h"
#include "File.h"
#include "Scheduler.h"

using namespace std;

INE5412::INE5412() {}

INE5412::INE5412(string _algorithm) { Scheduler sched(_algorithm); }

INE5412::~INE5412() {}

__int64_t INE5412::getStackPointer() { return this->stackPointer; }
__int64_t INE5412::getProgramCounter() { return this->programCounter; }
__int64_t INE5412::getStatus() { return this->status; }
void INE5412::setStackPoint(__int64_t _stackPointer) { this->stackPointer = _stackPointer; }
void INE5412::setProgramCounter(__int64_t _programCounter) { this->programCounter = _programCounter; }
void INE5412::setStatus(__int64_t _status) { this->status = _status; }
