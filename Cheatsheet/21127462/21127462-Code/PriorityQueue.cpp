#include "PriorityQueue.h"


PriorityQueue::PriorityQueue(CompareProcesses compareProcesses)
{
	compare = compareProcesses;
}

void PriorityQueue::push(Process* process, int t)
{
	process->setArrivalQueue(t);
	waitingProcesses.push_back(process);
	heapifyFromBot(waitingProcesses.size() - 1);
}

void PriorityQueue::pop()
{
	int last = waitingProcesses.size() - 1;
	swap(waitingProcesses[0], waitingProcesses[last]);
	waitingProcesses.pop_back();
	heapifyFromTop(0);
}

Process* PriorityQueue::first()
{
	if (isEmpty() == 0)
		return waitingProcesses[0];
	else
		return nullptr;
}

void PriorityQueue::heapifyFromBot(int rootIndex)
{
	int parent = (rootIndex - 1) / 2;
	if (parent >= 0)
	{
		if (compare(waitingProcesses[parent], waitingProcesses[rootIndex]) == 1)
		{
			swap(waitingProcesses[parent], waitingProcesses[rootIndex]);
			heapifyFromBot(parent);
		}
	}
}

void PriorityQueue::heapifyFromTop(int rootIndex)
{
	int child = rootIndex * 2 + 1;
	int parent = rootIndex;
	while (child < waitingProcesses.size())
	{
		if (child < waitingProcesses.size() - 1)
		{
			if (compare(waitingProcesses[child], waitingProcesses[child + 1]))
				++child;
		}

		if (compare(waitingProcesses[child], waitingProcesses[parent]))
			return;

		swap(waitingProcesses[parent], waitingProcesses[child]);
		parent = child;
		child = 2 * parent + 1;
	}
}



bool PriorityQueue::isEmpty()
{
	return waitingProcesses.size() == 0;
}

int PriorityQueue::size()
{
	return waitingProcesses.size();
}

