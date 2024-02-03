#include "Schedule.h"

#include "Derived.h"

Schedule::Schedule(string file) : upcomingProcesses(Process::ArrivalTimeCompare)
{
	fstream f;
	f.open(file, ios::in);
	int type;
	f >> type;

	switch (type)
	{
	case S_FCFS:
		algorithm = new FCFS();
		break;
	case S_RR:
		int q; f >> q;
		algorithm = new RR(q);
		break;
	case S_SJF:
		algorithm = new SJF();
		break;
	case S_SRTN:
		algorithm = new SRTN();
		break;

	default:
		algorithm = nullptr;
	}

	f >> n;
	f.ignore(1000, '\n');

	for (int i = 0; i < n; ++i)
	{
		string line = "";

		getline(f, line);
		stringstream ss(line);
		float arrival;
		vector<int> burst;
		ss >> arrival;
		while (!ss.eof())
		{
			int tmp;
			ss >> tmp;
			burst.push_back(tmp);
		}
		Process* tmp = new Process(to_string(i + 1), arrival, burst);
		upcomingProcesses.push(tmp, 0);
		processesList.push_back(tmp);
	}

	f.close();
}

Schedule::~Schedule()
{
	for (Process* i : processesList)
		delete i;
	delete algorithm;
}

bool Schedule::isCompleted()
{
	return (upcomingProcesses.isEmpty() && algorithm->isCompleted());
}


void Schedule::printCpuChart()
{
	cout << cpuChart << "\n";
}

void Schedule::printIoChart()
{
	cout << ioChart << "\n";
}

void Schedule::printTT()
{
	for (int i = 0; i < n; ++i)
	{
		cout << processesList[i]->getTT() << " ";
	}
	cout << "\n";
}

void Schedule::printWT()
{
	for (int i = 0; i < n; ++i)
	{
		cout << processesList[i]->getWT() << " ";
	}
	cout << "\n";
}

void Schedule::run()
{
	int i = 0;
	while (isCompleted() == 0)
	{
		while (upcomingProcesses.isEmpty() == 0 && upcomingProcesses.first()->getArrivalTime() == i)
		{
			algorithm->addProcess(upcomingProcesses.first(), i);
			upcomingProcesses.pop();
		}

		algorithm->execute(cpuChart, ioChart, i);

		++i;
	}
}

void Schedule::exportOutput(string file)
{
	fstream f;
	f.open(file, ios::out);

	f << cpuChart << "\n";
	f << ioChart << "\n";

	for (Process* i : processesList)
		f << i->getTT() << " ";

	f << "\n";

	for (Process* i : processesList)
		f << i->getWT() << " ";

	f << "\n";
}
