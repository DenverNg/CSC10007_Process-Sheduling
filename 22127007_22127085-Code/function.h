#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Process
{
public:
    // Variables for testing
    int index;
    bool isCompleted;
    // Variables for scheduling
    int arrivalTime;
    int cpuBurstTime[3];
    int resourceUsageTime[3];
    // Default constructor
    Process() : index(0), isCompleted(0), arrivalTime(0)
    {
        for (int i = 0; i < 3; ++i)
        {
            cpuBurstTime[i] = 0;
            resourceUsageTime[i] = 0;
        }
    }

    // Parameterized constructor
    Process(int index, bool isCompleted, int arrival, int cpu1, int cpu2, int cpu3, int res1, int res2, int res3)
        :index(index), isCompleted(0), arrivalTime(arrival)
    {
        cpuBurstTime[0] = cpu1;
        cpuBurstTime[1] = cpu2;
        cpuBurstTime[2] = cpu3;

        resourceUsageTime[0] = res1;
        resourceUsageTime[1] = res2;
        resourceUsageTime[2] = res3;
    }
};

class Scheduler
{
private:
    vector<Process> processes;
    int schedulingAlgorithm;
    int timeQuantum;
    // Member variables for Gantt charts
    vector<int> cpuSchedule;
    vector<int> resourceSchedule;
    // Member variables for output
public:
    Scheduler(const string &inputFile, const string &outputFile);

private:
    void readInput(const string &inputFile);
    void executeScheduling();
    void fcfsScheduling(vector<Process> &processes);
    void sjfScheduling();
    void srtnScheduling();
    void roundRobinScheduling();
    void writeOutput(const string &outputFile);
};
