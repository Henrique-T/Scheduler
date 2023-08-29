#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "processParams.h"

using namespace std;

ProcessParams::ProcessParams(int c, int d, int p)
{
	creation_time = c;
	duration = d;
	priority = p;
}

ProcessParams::~ProcessParams()
{
}

int ProcessParams::getCreationTime()
{
	return this->creation_time;
}

int ProcessParams::getDuration()
{
	return this->duration;
}

int ProcessParams::getPriority()
{
	return this->priority;
}

void ProcessParams::setCreationTime(int creationTime)
{
	this->creation_time = creationTime;
}

void ProcessParams::setDuration(int duration)
{
	this->duration = duration;
}

void ProcessParams::setPriority(int priority)
{
	this->priority = priority;
}

// int main()
// {
// 	File f;
// 	f.read_file();
// 	f.print_processes_params();
// }
