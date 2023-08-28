#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "processParams.h"

using namespace std;

/*
	Represents the input .txt file.
*/
class file
{
public:
	file();
	~file();
	/**/
	void read_file();
	/**/
	void print_processes_params();
	/**/
	vector<processParams *> getProcesses();

private:
	ifstream myfile;
	vector<processParams *> processes;
};

#endif