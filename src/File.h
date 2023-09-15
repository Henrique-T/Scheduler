#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ProcessParams.h"

using namespace std;

/*
	Represents the input .txt file.
*/
class File
{
private:
	ifstream myfile;
	vector<ProcessParams *> processes;

public:
	File();
	~File();
	/**/
	void read_file();
	/**/
	void print_processes_params();
	/**/
	vector<ProcessParams *> getProcesses();
};

#endif