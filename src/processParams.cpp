#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "processParams.h"

using namespace std;

processParams::processParams(int c, int d, int p)
{
	creation_time = c;
	duration = d;
	priority = p;
}

processParams::~processParams()
{
}

// int main()
// {
// 	File f;
// 	f.read_file();
// 	f.print_processes_params();
// }
