#include"Algorithm.h"

class Scheduler
{
private:
    PriorityQueue upcomingProcesses;
    vector<Process*> processesList;
    Algorithm* algorithm;
    string cpuChart;
    string ioChart;
    int numProcesses;
public:
    Scheduler(string inputFile);
    ~Scheduler();

    bool isCompleted();

    void printCpuChart();
    void printIoChart();

    void printTT();
    void printWT();

    void run();

    void exportOutput(string outputFile);
};