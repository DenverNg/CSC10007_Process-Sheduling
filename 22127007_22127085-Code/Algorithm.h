#pragma once
#include "Process.h"

class Algorithm
{
protected:
    PriorityQueue CPUQueue, IOQueue;
    Process *cpuRunning = nullptr, *ioRunning = nullptr;

public:
    Algorithm(CompareProcesses compareProcesses);
    Algorithm(CompareProcesses compareProcesses, fstream &f);
    void addProcess(Process *process, int t);

    virtual bool isCompleted();
    void virtual readFile(fstream &f);
    void virtual execute(string &cpuChart, string &ioChart, int t);
};

// ----------------- Derived Classes -----------------
// FCFS
class FCFS : public Algorithm
{
public:
    FCFS() : Algorithm(Process::FCFSCompare) {}
};

// RR
class RR : public Algorithm
{
private:
    int quantum, count;

public:
    RR(int q) : Algorithm(Process::FCFSCompare), quantum(q), count(q) {}
    void execute(string &cpuChart, string &ioChart, int t) override;
};

// SJF
class SJF : public Algorithm
{
public:
    SJF() : Algorithm(Process::SJFCompare) {}
};

// SRTN
class SRTN : public Algorithm
{
public:
    SRTN() : Algorithm(Process::SJFCompare) {}
    void execute(string &cpuChart, string &ioChart, int t) override;
};
