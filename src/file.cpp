#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "processParams.h"
#include "File.h"

using namespace std;

File::File()
{
	myfile.open("entrada.txt");
	if (!myfile.is_open())
	{
		cout << "Erro ao abrir o arquivo!\n";
	}
}

File::~File()
{
	for (int i = 0; i < processes.size(); i++)
	{
		processParams *p = processes[i];
		delete p;
	}
}

void File::read_file()
{

	int a, b, c;

	if (!myfile.is_open())
	{
		cout << "Arquivo não está aberto!" << endl;
	}

	while (myfile >> a >> b >> c)
	{
		processParams *p = new processParams(a, b, c);
		processes.push_back(p);
	}

	cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
}

void File::print_processes_params()
{
	vector<processParams *>::iterator iter = processes.begin();

	for (iter; iter < processes.end(); iter++)
	{
		processParams *p = *iter;
		cout << *p;
	}
}

vector<processParams *> File::getProcesses()
{
	return this->processes;
}