#ifndef PROCESS_PARAMS_H
#define PROCESS_PARAMS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
	Processes the input .txt file.
	Reads creation time, duration and priority for each process.
*/
class ProcessParams
{
public:
	ProcessParams(int c, int d, int p);
	~ProcessParams();
	int getCreationTime();
	int getDuration();
	int getPriority();
	void setCreationTime(int creationTime);
	void setDuration(int duration);
	void setPriority(int priority);

	friend ostream &operator<<(ostream &os, const ProcessParams &p)
	{
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}

private:
	int creation_time;
	int duration; //seconds
	int priority;
};

#endif