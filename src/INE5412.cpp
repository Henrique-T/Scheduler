#include "INE5412.h"
#include "ProcessParams.h"
#include "File.h"
#include "Scheduler.h"

using namespace std;

INE5412::INE5412() {}

INE5412::INE5412(string _algorithm)
{
	Scheduler sched(_algorithm);
}

INE5412::~INE5412() {}
