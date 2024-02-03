#include "Scheduler.h"

Scheduler::Scheduler(string inputFile) : upcomingProcesses(Process::ArrivalTimeCompare)
{
    ifstream inp(inputFile);
    if (!inp.is_open())
    {
        cout << "Error: Unable to open input file" << endl;
        return;
    }

    int type;
    inp >> type;
    cout << "Type: " << type << endl;
    switch (type)
    {
    case 1:
        algorithm = new FCFS();
        break;
    case 2:
        int q;
        inp >> q;
        cout << "Time quantum: " << q << endl;
        algorithm = new RR(q);
        break;
    case 3:
        algorithm = new SJF();
        break;
    case 4:
        algorithm = new SRTN();
        break;

    default:
        algorithm = nullptr;
        cout << "Invalid scheduling algorithm specified" << endl;
    }

    inp >> numProcesses;
    inp.ignore(1000, '\n');
    cout << "Number of processes: " << numProcesses << endl;
    cout << "Processes:" << endl;
    for (int i = 0; i < numProcesses; ++i)
    {
        string line = "";
        getline(inp, line);
        stringstream ss(line);
        float arrival;
        vector<int> burst;
        ss >> arrival;
        cout << arrival << " ";
        while (!ss.eof())
        {
            int tmp;
            ss >> tmp;
            cout << tmp << " ";
            burst.push_back(tmp);
        }
        Process *tmp = new Process(to_string(i + 1), arrival, burst);
        upcomingProcesses.push(tmp, 0);
        processesList.push_back(tmp);
        cout << endl;
    }
    inp.close();
}

Scheduler::~Scheduler()
{
    for (Process *i : processesList)
        delete i;
    delete algorithm;
}

bool Scheduler::isCompleted()
{
    return (upcomingProcesses.isEmpty() && algorithm->isCompleted());
}

void Scheduler::printCpuChart()
{
    cout << "CPU: ";
    cout << cpuChart << "\n";
}

void Scheduler::printIoChart()
{
    cout << "IO : ";
    cout << ioChart << "\n";
}

void Scheduler::printTT()
{
    cout << "TT : ";
    for (int i = 0; i < numProcesses; ++i)
    {
        cout << processesList[i]->getTT() << " ";
    }
    cout << "\n";
}

void Scheduler::printWT()
{
    cout << "WT : ";
    for (int i = 0; i < numProcesses; ++i)
    {
        cout << processesList[i]->getWT() << " ";
    }
    cout << "\n";
}

void Scheduler::run()
{
    int i = 0;
    while (isCompleted() == 0)
    {
        while (upcomingProcesses.isEmpty() == 0 && upcomingProcesses.first()->getArrivalTime() == i)
        {
            algorithm->addProcess(upcomingProcesses.first(), i);
            upcomingProcesses.pop();
        }

        algorithm->execute(cpuChart, ioChart, i);

        ++i;
    }
}

void Scheduler::exportOutput(string outputFile)
{
    ofstream out;
    out.open(outputFile);
    if (!out.is_open())
    {
        cout << "Error: Unable to open output file" << endl;
        return;
    }
    // Print output to screen
    cout << endl;
    printCpuChart();
    printIoChart();
    printTT();
    printWT();
    // Print output to file

    out << cpuChart << "\n";
    out << ioChart << "\n";
    for (Process *i : processesList)
        out << i->getTT() << " ";

    out << "\n";
    for (Process *i : processesList)
        out << i->getWT() << " ";
    out << "\n";
}