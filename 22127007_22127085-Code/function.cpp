// function.cpp
#include "function.h"

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
    //cout << schedulingAlgorithm << " " << timeQuantum << " ";
    int numProcesses;
    while (!(infile >> numProcesses) || numProcesses <= 0 || numProcesses > 4)
    {
        cout << "Error: Invalid number of processes.\n";
        exit(EXIT_FAILURE);
    }
    //cout << numProcesses << endl;
    processes.resize(numProcesses);

    string line;
    infile.ignore();
    for (int i = 0; i < numProcesses; ++i)
    {
        processes[i].index=i+1;
        processes[i].isCompleted=0;
        getline(infile, line);
        //cout << line << endl;
        istringstream iss(line);
        iss >> processes[i].arrivalTime;
        for (int j = 0; j < 3; ++j)
        {
            iss >> processes[i].cpuBurstTime[j];
            if (processes[i].cpuBurstTime[j] == 0)
                break;
            iss >> processes[i].resourceUsageTime[j];
        }
    }
    //cout << endl;
    // for (int i=0;i<numProcesses;i++)
    // {
    //     cout << processes[i].arrivalTime << " ";
    //     for (int j=0;j<3;j++)
    //     {
    //         cout << processes[i].cpuBurstTime[j] << " " << processes[i].resourceUsageTime[j] << " ";
    //     }
    //     cout << endl;
    // }
    infile.close();
}

void Scheduler::executeScheduling()
{
    switch (schedulingAlgorithm)
    {
    case 1: // FCFS
        fcfsScheduling(processes);
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

void Scheduler::fcfsScheduling(vector<Process> &processes)
{
    // Implement FCFS scheduling logic here
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });
    
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
    for (int i : cpuSchedule)
    {
        if (i!=0)
            outfile << i << " ";
        else outfile << "_ ";
    }
    outfile << "\n";

    // Print Gantt chart for resource scheduling to the output file
    for (int i : resourceSchedule)
    {
        if (i != 0)
            outfile << i << " ";
        else
            outfile << "_ ";
    }
    outfile << "\n";

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
