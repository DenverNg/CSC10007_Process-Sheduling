#pragma once
#include "PriorityQueue.h"
#include "SchedulingAlgorithm.h"


class Schedule
{
private:
	PriorityQueue upcomingProcesses;
	vector <Process*> processesList;
	SchedulingAlgorithm* algorithm;
	string cpuChart;
	string ioChart;
	int n;
public:
	Schedule(string file);
	~Schedule();

	bool isCompleted();

	void printCpuChart();
	void printIoChart();

	void printTT();
	void printWT();

	void run();

	void exportOutput(string file);

};