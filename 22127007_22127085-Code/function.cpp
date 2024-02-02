// function.cpp
#include "function.h"

Process::Process() : arrivalTime(0), turnAroundTime(0), waitingTime(0)
{
    for (int i = 0; i < 6; ++i)
    {
        Task[i] = 0;
    }
    curTaskPos = 0;
}

Process::Process(int at, int tt, int wt)
    : arrivalTime(at), turnAroundTime(tt), waitingTime(wt)
{
    for (int i = 0; i < 6; ++i)
    {
        Task[i] = 0;
    }
    curTaskPos = 0;
}

Process::Process(const Process &other)
{
    arrivalTime = other.arrivalTime;
    turnAroundTime = other.turnAroundTime;
    waitingTime = other.waitingTime;
    for (int i = 0; i < 6; ++i)
    {
        Task[i] = other.Task[i];
    }
    curTaskPos = other.curTaskPos;
}

int Process::getArrivalTime() const
{
    return arrivalTime;
}

int Process::getCurTask()
{
    for (int i = 0; i < 6; i++)
    {
        if (Task[i] != 0)
        {
            curTaskPos = i;
            return Task[i];
        }
    }
    curTaskPos = -1; // no task left
    return 0;
}

int Process::getCurBurstTime()
{
    for (int i = 0; i < 6; i++)
    {
        if (Task[i] != 0 && i % 2 == 0)
        {
            return Task[i];
        }
    }
    return 0;
}

void Process::decreaseCurTask()
{
    Task[curTaskPos]--;
}

Process &Process::operator=(const Process &other)
{
    arrivalTime = other.arrivalTime;
    turnAroundTime = other.turnAroundTime;
    waitingTime = other.waitingTime;
    for (int i = 0; i < 6; ++i)
    {
        Task[i] = other.Task[i];
    }
    curTaskPos = other.curTaskPos;
    return *this;
}

Scheduler::Scheduler() : schedulingAlgorithm(0), numProcesses(0), timeQuantum(0), numCompleted(0), curTime(0)
{
}

Scheduler::Scheduler(const string &inputFile, const string &outputFile)
{
    readInput(inputFile);
    executeScheduling();
    writeOutput(outputFile);
}

void Scheduler::readInput(const string &inputFile)
{
    ifstream infile(inputFile);
    if (!infile.is_open())
    {
        cout << "Error: Unable to open input file.\n";
        exit(EXIT_FAILURE);
    }

    infile >> schedulingAlgorithm;

    if (schedulingAlgorithm == 2)
    { // Round Robin
        infile >> timeQuantum;
    }
    cout << "Type: " << schedulingAlgorithm << endl;
    if (schedulingAlgorithm == 2)
        cout << "Time quantum: " << timeQuantum << endl;
    while (!(infile >> numProcesses) || numProcesses <= 0 || numProcesses > 4)
    {
        cout << "Error: Invalid number of processes.\n";
        exit(EXIT_FAILURE);
    }
    cout << "Num Processes: " << numProcesses << endl;
    processes.resize(numProcesses);

    string line;
    infile.ignore();
    for (int i = 0; i < numProcesses; i++)
    {
        getline(infile, line);
        cout << line << endl;
        istringstream iss(line);
        iss >> processes[i].arrivalTime;
        // processes[i].index = i + 1;
        for (int j = 0; j < 6; ++j)
        {
            iss >> processes[i].Task[j];
        }
    }
    cout << endl;
    for (int i = 0; i < numProcesses; i++)
    {
        // cout << processes[i].index << " ";
        cout << processes[i].arrivalTime << " ";
        for (int j = 0; j < 6; j++)
        {
            cout << processes[i].Task[j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    infile.close();
}

void Scheduler::executeScheduling()
{
    switch (schedulingAlgorithm)
    {
    case 1: // FCFS
        fcfsScheduling();
        break;
    case 2: // Round Robin
        roundRobinScheduling();
        break;
    case 3: // SJF (Shortest Job First)
        sjfScheduling();
        break;
    case 4: // SRTN (Shortest Remaining Time Next)
        srtnScheduling();
        break;
    default:
        cout << "Invalid scheduling algorithm specified.\n";
        exit(EXIT_FAILURE);
    }
}

// Implement FCFS scheduling logic here
void Scheduler::fcfsConcrete(vector<char> &Schedule, queue<int> &Queue, queue<int> &otherQueue)
{
    if (Queue.empty())
    {
        Schedule.push_back('_');
        return;
    }

    int First = Queue.front();
    int curTask = processes[First].getCurTask();
    string firstStr = to_string(First + 1);
    for (char c : firstStr)
        Schedule.push_back(c);
    if (curTask == 1)
        Queue.pop();
    processes[First].decreaseCurTask();
    if (processes[First].getCurTask() == 0)
    {
        numCompleted++;
        return;
    }

    if (First != Queue.front())
        otherQueue.push(First);
}

void Scheduler::fcfsScheduling()
{
    while (numCompleted != numProcesses)
    {
        for (int i = 0; i < processes.size(); i++)
            if (processes[i].getArrivalTime() == curTime)
            {
                cpuQueue.push(i);
            }
        if (cpuQueue.empty() && resourceQueue.empty())
        {
            cpuSchedule.push_back('_');
            resourceSchedule.push_back('_');
        }
        else if ((!cpuQueue.empty() || processes[resourceQueue.front()].getCurTask() != 1) || (resourceQueue.empty() && processes[cpuQueue.front()].getCurTask() == 1))
        {
            fcfsConcrete(resourceSchedule, resourceQueue, cpuQueue);
            fcfsConcrete(cpuSchedule, cpuQueue, resourceQueue);
        }
        else
        {
            fcfsConcrete(cpuSchedule, cpuQueue, resourceQueue);
            fcfsConcrete(resourceSchedule, resourceQueue, cpuQueue);
        }
        curTime++;
    }
    for (int i = 0; i < cpuSchedule.size(); i++)
    {
        cout << cpuSchedule[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < resourceSchedule.size(); i++)
    {
        cout << resourceSchedule[i] << " ";
    }
}

// Implement Round Robin scheduling logic here

void Scheduler::rrConcrete(vector<char> &Schedule, queue<int> &Queue, queue<int> &otherQueue, int &countDown)
{
    if (Queue.empty())
    {
        Schedule.push_back('_');
        return;
    }
    int First = Queue.front();

    int curTask = processes[First].getCurTask();
    string firstStr = to_string(First + 1);
    for (char c : firstStr)
        Schedule.push_back(c);

    processes[First].decreaseCurTask();
    countDown--;

    if (processes[First].getCurTask() == 0)
    {
        numCompleted++;
        Queue.pop();
        if (countDown == 0)
            countDown = timeQuantum;
        return;
    }

    int curTaskPos = processes[First].curTaskPos;

    if (countDown == 0)
    {
        Queue.pop();
        if (curTask != 1)
            Queue.push(First);
        else
            otherQueue.push(First);
        countDown = timeQuantum;
    }
    else if (curTask == 1)
    {
        Queue.pop();
        countDown = timeQuantum;
        if (curTaskPos != -1)
            otherQueue.push(First);
    }
}

void Scheduler::roundRobinScheduling()
{
    // sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
    //      { return a.arrivalTime < b.arrivalTime; });

    int countDown = timeQuantum;
    while (numCompleted != numProcesses)
    {
        for (int i = 0; i < processes.size(); i++)
        {
            if (processes[i].getArrivalTime() == curTime)
            {
                cpuQueue.push(i);
            }
        }
        if (cpuQueue.empty() && resourceQueue.empty())
        {
            cpuSchedule.push_back('_');
            resourceSchedule.push_back('_');
        }
        else if ((!cpuQueue.empty() || processes[resourceQueue.front()].getCurTask() != 1) || (resourceQueue.empty() && processes[cpuQueue.front()].getCurTask() == 1))
        {
            fcfsConcrete(resourceSchedule, resourceQueue, cpuQueue);
            rrConcrete(cpuSchedule, cpuQueue, resourceQueue, countDown);
        }
        else
        {
            rrConcrete(cpuSchedule, cpuQueue, resourceQueue, countDown);
            fcfsConcrete(resourceSchedule, resourceQueue, cpuQueue);
        }
        curTime++;
    }
    for (int i = 0; i < cpuSchedule.size(); i++)
    {
        cout << cpuSchedule[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < resourceSchedule.size(); i++)
    {
        cout << resourceSchedule[i] << " ";
    }
}

// Implement SRTN scheduling logic here
void Scheduler::srtnConcrete(vector<char> &Schedule, queue<int> &Queue, queue<int> &otherQueue)
{
    if (Queue.empty())
    {
        Schedule.push_back('_');
        return;
    }

    int First = Queue.front();
    int curTask = processes[First].getCurTask();
    string firstStr = to_string(First + 1);
    for (char c : firstStr)
        Schedule.push_back(c);
    Queue.pop();
    processes[First].decreaseCurTask();

    if (processes[First].getCurTask() == 0)
    {
        numCompleted++;
        return;
    }
    else
        otherQueue.push(First);
}

void Scheduler::srtnScheduling()
{
    int smallestBurstTime = 0;
    int index=0;
    while (numCompleted != numProcesses)
    {
        for (int i = 0; i < processes.size(); i++)
        {
            if (processes[i].getArrivalTime() <= curTime && processes[i].getCurBurstTime() <= processes[smallestBurstTime].getCurBurstTime())
            {
                smallestBurstTime = i;
                cpuQueue.push(i);
            }
        }
        if (cpuQueue.empty() && resourceQueue.empty())
        {
            cpuSchedule.push_back('_');
            resourceSchedule.push_back('_');
        }
        else if ((!cpuQueue.empty() || processes[resourceQueue.front()].getCurTask() != 1) || (resourceQueue.empty() && processes[cpuQueue.front()].getCurTask() == 1))
        {
            fcfsConcrete(resourceSchedule, resourceQueue, cpuQueue);
            srtnConcrete(cpuSchedule, cpuQueue, resourceQueue);
        }
        else
        {
            srtnConcrete(cpuSchedule, cpuQueue, resourceQueue);
            fcfsConcrete(resourceSchedule, resourceQueue, cpuQueue);
        }
        curTime++;
    }
    for (int i = 0; i < cpuSchedule.size(); i++)
    {
        cout << cpuSchedule[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < resourceSchedule.size(); i++)
    {
        cout << resourceSchedule[i] << " ";
    }
}

// Implement SJF scheduling logic here
void Scheduler::sjfConcrete(vector<char> &Schedule, queue<int> &Queue, queue<int> &otherQueue)
{
    if (Queue.empty())
    {
        Schedule.push_back('_');
        return;
    }

    int First = Queue.front();
    int curTask = processes[First].getCurTask();
    string firstStr = to_string(First + 1);
    for (char c : firstStr)
        Schedule.push_back(c);
    Queue.pop();
    processes[First].decreaseCurTask();

    if (processes[First].getCurTask() == 0)
    {
        numCompleted++;
        return;
    }
    else
        otherQueue.push(First);
}

void Scheduler::sjfScheduling()
{

}

void Scheduler::writeOutput(const string &outputFile)
{
    ofstream outfile(outputFile);
    if (!outfile.is_open())
    {
        cout << "Error: Unable to open output file.\n";
        exit(EXIT_FAILURE);
    }
    // Print Gantt chart for CPU scheduling to the output file
    for (int i = 0; i < cpuSchedule.size(); i++)
    {
        outfile << cpuSchedule[i] << " ";
    }
    outfile << endl;
    // Print Gantt chart for resource scheduling to the output file
    for (int i = 0; i < resourceSchedule.size(); i++)
    {
        outfile << resourceSchedule[i] << " ";
    }

    outfile.close();
}
