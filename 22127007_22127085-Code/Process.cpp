#include"Process.h" 

Process::Process(string id, int arrival, vector<int> seq) : name(id), arrivalTime(arrival), waitingTime(0), turnaroundTime(0), arrivalQueue(0)
{
    for (int i : seq)
        sequence.push(i);
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

void Process::setJustFinishIO(bool value)
{
    justFinishIO = value;
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

void Process::setArrivalQueue(int value)
{
    arrivalQueue = value;
}

bool Process::processDone()
{
    return sequence.front() == 0;
}

void Process::run()
{
    sequence.front()--;
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

bool Process::ArrivalTimeCompare(Process *a, Process *b)
{
    return a->arrivalTime > b->arrivalTime;
}

bool Process::FCFSCompare(Process *a, Process *b)
{
    if (a->arrivalQueue == b->arrivalQueue)
    {
        if (a->isNew == b->isNew) // both are not new
            return a->justFinishIO < b->justFinishIO;
        else
            return a->isNew < b->isNew;
    }
    else
        return a->arrivalQueue > b->arrivalQueue;
}

bool Process::SJFCompare(Process *a, Process *b)
{
    if (a->getFirstBurst() == b->getFirstBurst())
    {
        if (a->isNew == b->isNew)
            return a->justFinishIO < b->justFinishIO;
        else
            return a->isNew < b->isNew;
    }
    else
        return a->getFirstBurst() > b->getFirstBurst();
}


// Implementation of the priority queue
PriorityQueue::PriorityQueue(CompareProcesses compareProcesses) : compare(compareProcesses) {}

void PriorityQueue::push(Process *process, int t)
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

Process *PriorityQueue::first()
{
    if (isEmpty() == 0)
        return waitingProcesses[0];
    else
        return nullptr;
}

bool PriorityQueue::isEmpty()
{
    return waitingProcesses.empty();
}

int PriorityQueue::size()
{
    return waitingProcesses.size();
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
        child = parent * 2 + 1;
    }
}