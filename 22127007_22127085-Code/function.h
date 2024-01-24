#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Process
{
public:
    int arrivalTime;
    int cpuBurstTime;
    int resourceUsageTime;
    // Default constructor
    Process() : arrivalTime(0), cpuBurstTime(0), resourceUsageTime(0) {}
    // Parameterized constructor
    Process(int arrival, int cpuBurst, int resourceUsage)
        : arrivalTime(arrival), cpuBurstTime(cpuBurst), resourceUsageTime(resourceUsage) {}
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

public:
    Scheduler(const string &inputFile, const string &outputFile);

private:
    void readInput(const string &inputFile);
    void executeScheduling();
    void fcfsScheduling();
    void sjfScheduling();
    void srtnScheduling();
    void roundRobinScheduling();
    void writeOutput(const string &outputFile);
};
