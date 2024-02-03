#pragma once

#include "SchedulingAlgorithm.h"

class FCFS : public SchedulingAlgorithm
{

public:
	FCFS() : SchedulingAlgorithm(Process::FCFSCompare) {}

};



class RR : public SchedulingAlgorithm
{
private:
	int quantum, count;

public:
	RR(int q) : SchedulingAlgorithm(Process::FCFSCompare), quantum(q), count(q) {}
	
	void execute(string& cpuChart, string& ioChart, int t) override
	{
		if (t == 17)
			cout << "";
		SchedulingAlgorithm::execute(cpuChart, ioChart, t);
		if (cpuRunning != nullptr)
			--count;
		else
			count = quantum;
		if (count == 0 && cpuRunning != nullptr)
		{
			CPUQueue.push(cpuRunning,t+1);
			cpuRunning = nullptr;
			count = quantum;
		}
	}
};


class SJF : public SchedulingAlgorithm
{
public:
	SJF() : SchedulingAlgorithm(Process::SJFCompare) {}

};


class SRTN : public SchedulingAlgorithm
{
public :
	SRTN() : SchedulingAlgorithm(Process::SJFCompare) {}

	void execute(string& cpuChart, string& ioChart, int t) override
	{
		SchedulingAlgorithm::execute(cpuChart, ioChart, t);
		if(cpuRunning!=nullptr)
			CPUQueue.push(cpuRunning, t + 1);
		cpuRunning = nullptr;
	}
	
};