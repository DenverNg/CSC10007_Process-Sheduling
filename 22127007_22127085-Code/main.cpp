#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;
class Process
{
public:
    int arrivalTime;
    int cpuBurstTime;
    int resourceUsageTime;

    Process(int arrival, int cpu_burst, int resource_usage)
        : arrivalTime(arrival), cpuBurstTime(cpu_burst), resourceUsageTime(resource_usage) {}
};

class Scheduler
{
private:
    vector<Process> processes;
    int schedulingAlgorithm;
    int timeQuantum;

public:
    Scheduler(const string &inputFile, const string &outputFile)
    {
        readInput(inputFile);
        executeScheduling();
        writeOutput(outputFile);
    }

private:
    void readInput(const string &inputFile)
    {
        ifstream infile(inputFile);
        if (!infile.is_open())
        {
            cerr << "Error: Unable to open input file.\n";
            exit(EXIT_FAILURE);
        }

        infile >> schedulingAlgorithm;

        if (schedulingAlgorithm == 2)
        { // Round Robin
            infile >> timeQuantum;
        }

        int numProcesses;
        infile >> numProcesses;

        processes.resize(numProcesses);

        for (int i = 0; i < numProcesses; ++i)
        {
            infile >> processes[i].arrivalTime >> processes[i].cpuBurstTime;

            // Read resourceUsageTime if available
            if (schedulingAlgorithm == 4 || schedulingAlgorithm == 2)
            {
                infile >> processes[i].resourceUsageTime;
            }
        }

        infile.close();
    }

    void executeScheduling()
    {
        switch (schedulingAlgorithm)
        {
        case 1: // FCFS
            fcfsScheduling();
            break;
        case 2: // Round Robin
            roundRobinScheduling();
            break;
        // Add cases for other scheduling algorithms if needed
        default:
            cerr << "Invalid scheduling algorithm specified.\n";
            exit(EXIT_FAILURE);
        }
    }

    void fcfsScheduling()
    {
        // Implement FCFS scheduling logic here
        // This is just a placeholder; you should replace it with your own logic
    }

    void roundRobinScheduling()
    {
        // Implement Round Robin scheduling logic here
        // This is just a placeholder; you should replace it with your own logic
    }

    void writeOutput(const string &outputFile)
    {
        ofstream outfile(outputFile);
        if (!outfile.is_open())
        {
            cerr << "Error: Unable to open output file.\n";
            exit(EXIT_FAILURE);
        }

        // Implement the logic to generate the output (Gantt chart, turn-around time, etc.)
        // ...

        outfile.close();
    }
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <inputFile> <outputFile>\n";
        return EXIT_FAILURE;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    Scheduler scheduler(inputFile, outputFile);

    cout << "Process scheduling complete. Output written to " << outputFile << endl;

    return EXIT_SUCCESS;
}
