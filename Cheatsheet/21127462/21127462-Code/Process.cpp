#include "Process.h"

Process::Process(string id, int arrival, vector<int> seq) : name(id), arrivalTime(arrival), waitingTime(0), turnaroundTime(0), arrivalQueue(0)
{
	for (int i : seq)
		sequence.push(i);
}

void Process::setArrivalQueue(int value)
{
	arrivalQueue = value;
}



string Process::getName()
{
	return name;
}

int Process::getArrivalTime()
{
	return arrivalTime;
}

int Process::getArrivalQueue()
{
	return arrivalQueue;
}

void Process::addWT(int value)
{
	waitingTime += value;
}

void Process::setTT(int value)
{
	turnaroundTime = value;
}

void Process::setJustIO(bool value)
{
	justIO = value;
}

int Process::getTT()
{
	return turnaroundTime;
}

int Process::getWT()
{
	return waitingTime;
}

int Process::getFirstBurst()
{
	return sequence.front();
}

bool Process::processDone()
{
	return sequence.front() == 0;
}

void Process::run()
{
	--sequence.front();
	isNew = 0;
}

void Process::removeDone()
{
	sequence.pop();
}

bool Process::everythingCompleted()
{
	return sequence.size() == 0;
}

bool Process::ArrivalTimeCompare(Process* a, Process* b)
{
	return a->arrivalTime > b->arrivalTime;
}

bool Process::FCFSCompare(Process* a, Process* b)
{
	if (a->arrivalQueue == b->arrivalQueue) 
	{
		if (a->isNew == b->isNew)   //both are not new 
			return a->justIO < b->justIO;
		else
			return a->isNew < b->isNew;
	}
	else
		return a->arrivalQueue > b->arrivalQueue;
}

bool Process::SJFCompare(Process* a, Process* b)
{
	if (a->getFirstBurst() == b->getFirstBurst())
	{
		if (a->isNew == b->isNew)
			return a->justIO < b->justIO;
		else
			return a->isNew < b->isNew;
	}
	else 
		return a->getFirstBurst() > b->getFirstBurst();
}