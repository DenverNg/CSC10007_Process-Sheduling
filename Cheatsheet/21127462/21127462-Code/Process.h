#pragma once
#include "header.h"


class Process
{
private:
	string name;
	queue <int> sequence;
	int arrivalTime, waitingTime, turnaroundTime;
	int arrivalQueue;
	bool isNew = 1, justIO = 0;

public:
	Process(string id, int arrival, vector<int> seq);

	string getName();
	int getArrivalTime();
	int getArrivalQueue();
	int getTT();
	int getWT();
	int getFirstBurst();


	void setArrivalQueue(int value);
	void setJustIO(bool value);
	void setTT(int value);
	void addWT(int value);

	bool processDone();

	void run();

	void removeDone();

	bool everythingCompleted();


	static bool ArrivalTimeCompare(Process* a, Process* b);
	static bool FCFSCompare(Process* a, Process* b);
	static bool SJFCompare(Process* a, Process* b);
};

typedef bool (*CompareProcesses) (Process*, Process*);