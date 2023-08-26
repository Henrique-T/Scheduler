#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "processParams.h"
#include "file.h"

using namespace std;

file::file()
{
	myfile.open("entrada.txt");
	if (!myfile.is_open())
	{
		cout << "Erro ao abrir o arquivo!\n";
	}
}

file::~file()
{
	for (int i = 0; i < processes.size(); i++)
	{
		processParams *p = processes[i];
		delete p;
	}
}

void file::read_file()
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

void file::print_processes_params()
{
	vector<processParams *>::iterator iter = processes.begin();

	for (iter; iter < processes.end(); iter++)
	{
		processParams *p = *iter;
		cout << *p;
	}
}