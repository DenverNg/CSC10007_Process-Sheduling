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

int Process::getArrivalTime()
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
    return 0;
}

void Process::decreaseCurTask()
{
    Task[curTaskPos]--;
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
     cout << schedulingAlgorithm;
    while (!(infile >> numProcesses) || numProcesses <= 0 || numProcesses > 4)
    {
        cout << "Error: Invalid number of processes.\n";
        exit(EXIT_FAILURE);
    }
      cout << numProcesses << endl;
    processes.resize(numProcesses);

    string line;
    infile.ignore();
    for (int i = 0; i < numProcesses; i++)
    {
        getline(infile, line);
         cout << line << endl;
        istringstream iss(line);
        iss >> processes[i].arrivalTime;
        for (int j = 0; j < 6; ++j)
        {
            iss >> processes[i].Task[j];
        }
    }
    cout << endl;
     for (int i=0;i<numProcesses;i++)
     {
         cout << processes[i].arrivalTime << " ";
         for (int j=0;j<6;j++)
         {
             cout << processes[i].Task[j] << " ";
         }
         cout << endl;
     }
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
    // Implement FCFS scheduling logic here
    // sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
    //      { return a.arrivalTime < b.arrivalTime; });

    int numLoaded = 0;
    while (numCompleted != numProcesses)
    {
        if (processes[numLoaded].getArrivalTime() == curTime)
        {
            cpuQueue.push(numLoaded);
            numLoaded++;
        }
        fcfsConcrete(resourceSchedule, resourceQueue, cpuQueue);
        fcfsConcrete(cpuSchedule, cpuQueue, resourceQueue);
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

void Scheduler::roundRobinScheduling()
{
    // Implement Round Robin scheduling logic here
}

void Scheduler::sjfScheduling()
{
    // Implement SJF (Shortest Job First) scheduling logic here
}

void Scheduler::srtnScheduling()
{
    // Implement SRTN (Shortest Remaining Time Next) scheduling logic here
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
    // // Calculate turn-around time and waiting time
    // int totalTurnAroundTime = 0;
    // int totalWaitingTime = 0;
    // int currentTime = 0;

    // for (const Process &process : processes)
    // {
    //     int turnAroundTime = currentTime - process.arrivalTime;
    //     int waitingTime = turnAroundTime - process.cpuBurstTime;
    //     totalTurnAroundTime += turnAroundTime;
    //     totalWaitingTime += waitingTime;

    //     // Move the current time to the end of the current process
    //     currentTime += process.cpuBurstTime;
    // }

    // // Print turn-around time for each process to the output file
    // for (const Process &process : processes)
    // {
    //     int turnAroundTime = currentTime - process.arrivalTime;
    //     outfile << turnAroundTime << " ";
    // }
    // outfile << "\n";

    // // Print waiting time for each process to the output file
    // for (const Process &process : processes)
    // {
    //     int turnAroundTime = currentTime - process.arrivalTime;
    //     int waitingTime = turnAroundTime - process.cpuBurstTime;
    //     outfile << waitingTime << " ";
    // }
    // outfile << "\n";

    outfile.close();
}
