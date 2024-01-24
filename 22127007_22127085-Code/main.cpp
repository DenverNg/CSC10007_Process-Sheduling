#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
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
        case 3: // SJF (Shortest Job First)
            sjfScheduling();
            break;
        case 4: // SRTN (Shortest Remaining Time Next)

            srtnScheduling();
            break;
        // Add cases for other scheduling algorithms if needed
        default:
            cerr << "Invalid scheduling algorithm specified.\n";
            exit(EXIT_FAILURE);
        }
    }

    void fcfsScheduling()
    {
        // Sort processes based on arrival time
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
             { return a.arrivalTime < b.arrivalTime; });

        // Initialize Gantt chart for CPU and resource scheduling
        int currentTime = 0;

        for (const Process &process : processes)
        {
            // Update CPU schedule
            for (int i = 0; i < process.cpuBurstTime; ++i)
            {
                cpuSchedule.push_back(process.arrivalTime);
            }

            // Update Resource schedule
            for (int i = 0; i < process.resourceUsageTime; ++i)
            {
                resourceSchedule.push_back(process.arrivalTime);
            }

            // Update current time
            currentTime += process.cpuBurstTime;

            // Add waiting time for the next process if there is a gap
            if (currentTime < process.arrivalTime)
            {
                for (int i = 0; i < process.arrivalTime - currentTime; ++i)
                {
                    cpuSchedule.push_back(0); // 0 denotes idle time
                    resourceSchedule.push_back(0);
                }
                currentTime = process.arrivalTime;
            }
        }
    }

    void roundRobinScheduling()
    {
        // Implement Round Robin scheduling logic here
    }

    void sjfScheduling()
    {
        // Implement SJF (Shortest Job First) scheduling logic here
    }

    void srtnScheduling()
    {
        // Implement SRTN (Shortest Remaining Time Next) scheduling logic here
    }
    
    void writeOutput(const string &outputFile)
    {
        ofstream outfile(outputFile);
        if (!outfile.is_open())
        {
            cerr << "Error: Unable to open output file.\n";
            exit(EXIT_FAILURE);
        }

        // Print Gantt chart for CPU scheduling to the output file
        for (int i : cpuSchedule)
        {
            outfile << i << " ";
        }
        outfile << "\n";

        // Print Gantt chart for resource scheduling to the output file
        for (int i : resourceSchedule)
        {
            outfile << i << " ";
        }
        outfile << "\n";

        // Calculate turn-around time and waiting time
        int totalTurnAroundTime = 0;
        int totalWaitingTime = 0;
        int currentTime = 0;

        for (const Process &process : processes)
        {
            int turnAroundTime = currentTime - process.arrivalTime;
            int waitingTime = turnAroundTime - process.cpuBurstTime;
            totalTurnAroundTime += turnAroundTime;
            totalWaitingTime += waitingTime;

            // Move the current time to the end of the current process
            currentTime += process.cpuBurstTime;
        }

        // Print turn-around time for each process to the output file
        for (const Process &process : processes)
        {
            int turnAroundTime = currentTime - process.arrivalTime;
            outfile << turnAroundTime << " ";
        }
        outfile << "\n";

        // Print waiting time for each process to the output file
        for (const Process &process : processes)
        {
            int turnAroundTime = currentTime - process.arrivalTime;
            int waitingTime = turnAroundTime - process.cpuBurstTime;
            outfile << waitingTime << " ";
        }
        outfile << "\n";

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
