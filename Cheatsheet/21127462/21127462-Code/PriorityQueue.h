#pragma once
#include "Process.h"


class PriorityQueue
{
private:
	CompareProcesses compare;
	vector <Process*> waitingProcesses;
public:

	PriorityQueue(CompareProcesses compareProcesses);

	void push(Process* process, int t);
	void pop();
	Process* first();

	bool isEmpty();
	int size();

	void heapifyFromBot(int rootIndex);
	void heapifyFromTop(int rootIndex);

	Process*& operator[](int i);
};
