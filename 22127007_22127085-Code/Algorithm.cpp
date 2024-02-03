#include "Algorithm.h"

Algorithm::Algorithm(CompareProcesses compareProcesses) : CPUQueue(compareProcesses), IOQueue(Process::FCFSCompare)
{
}

Algorithm::Algorithm(CompareProcesses compareProcesses, fstream &f) : CPUQueue(compareProcesses), IOQueue(Process::FCFSCompare)
{
    readFile(f);
}

void Algorithm::addProcess(Process *process, int t)
{
    CPUQueue.push(process, t);
}

bool Algorithm::isCompleted()
{
    return cpuRunning == nullptr && ioRunning == nullptr && CPUQueue.isEmpty() && IOQueue.isEmpty();
}

void Algorithm::readFile(fstream &f)
{
}

void Algorithm::execute(string &cpuChart, string &ioChart, int t)
{
    Process *tmp = nullptr;

    if (cpuRunning == nullptr && CPUQueue.isEmpty() == 0)
    {
        cpuRunning = CPUQueue.first();
        cpuRunning->addWT(t - cpuRunning->getArrivalQueue());
        CPUQueue.pop();
    }

    if (ioRunning == nullptr && IOQueue.isEmpty() == 0)
    {
        ioRunning = IOQueue.first();
        IOQueue.pop();
    }

    if (cpuRunning != nullptr)
    {
        cpuRunning->run();
        cpuChart += cpuRunning->getName() + " ";
        if (cpuRunning->processDone())
        {
            cpuRunning->removeDone();
            if (cpuRunning->everythingCompleted() == 0)
            {
                cpuRunning->setJustFinishIO(0);
                IOQueue.push(cpuRunning, t + 1);
            }
            else
                cpuRunning->setTT(t + 1 - cpuRunning->getArrivalTime());
            cpuRunning = nullptr;
        }
    }
    else
        cpuChart += "_ ";

    if (ioRunning != nullptr)
    {
        ioRunning->run();
        ioChart += ioRunning->getName() + " ";
        if (ioRunning->processDone())
        {
            ioRunning->removeDone();
            if (ioRunning->everythingCompleted() == 0)
            {
                ioRunning->setJustFinishIO(1);
                CPUQueue.push(ioRunning, t + 1);
            }
            else
                ioRunning->setTT(t + 1 - ioRunning->getArrivalTime());
            ioRunning = nullptr;
        }
    }
    else
        ioChart += "_ ";
}

void RR::execute(string &cpuChart, string &ioChart, int t)
{
    if (t == 17)
        cout << "";
    Algorithm::execute(cpuChart, ioChart, t);
    if (cpuRunning != nullptr)
        --count;
    else
        count = quantum;
    if (count == 0 && cpuRunning != nullptr)
    {
        CPUQueue.push(cpuRunning, t + 1);
        cpuRunning = nullptr;
        count = quantum;
    }
}

void SRTN::execute(string &cpuChart, string &ioChart, int t)
{
    Algorithm::execute(cpuChart, ioChart, t);
    if (cpuRunning != nullptr)
        CPUQueue.push(cpuRunning, t + 1);
    cpuRunning = nullptr;
}