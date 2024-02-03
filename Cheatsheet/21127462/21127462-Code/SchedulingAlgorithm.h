#pragma once
#include "PriorityQueue.h"


class SchedulingAlgorithm
{
protected:

	PriorityQueue CPUQueue, IOQueue;
	Process* cpuRunning = nullptr, * ioRunning = nullptr;

public:

	SchedulingAlgorithm(CompareProcesses compareProcesses) ;
	SchedulingAlgorithm(CompareProcesses compareProcesses, fstream& f) ;
	void addProcess(Process* process, int t);

	virtual bool isCompleted();
	void virtual readFile(fstream& f);
	void virtual execute(string& cpuChart, string& ioChart, int t);

};
