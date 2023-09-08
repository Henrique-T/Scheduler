#ifndef INE5412_H
#define INE5412_H

#include <sys/types.h>
#include "ContextProcess.h"
#include "Process.h"
#include "ContextCPU.h"
#include "ProcessParams.h"
#include <vector>

using namespace std;

/*
	Represents a cpu.
*/
class INE5412
{
private:
	/* data */
	ContextCPU _contextCPU;

public:
	INE5412();
	INE5412(string _algorithm);
	~INE5412();
};

#endif