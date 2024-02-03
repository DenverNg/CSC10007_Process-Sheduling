#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

class Process
{
private:
    string name;
    queue<int> sequence;
    int arrivalTime, waitingTime, turnaroundTime;
    int arrivalQueue;
    bool isNew = 1, justFinishIO = 0;

public:
    // Constructor
    Process(string id, int arrival, vector<int> seq);

    // Getters functions
    string getName();
    int getArrivalTime();
    int getArrivalQueue();
    int getTT();
    int getWT();
    int getFirstBurst();

    // Setters functions
    void setArrivalQueue(int value);
    void setJustFinishIO(bool value);
    void setTT(int value);
    void addWT(int value);

    // Process functions
    bool processDone();
    void run();
    void removeDone();
    bool everythingCompleted();

    // Static functions to compare processes
    static bool ArrivalTimeCompare(Process *a, Process *b);
    static bool FCFSCompare(Process *a, Process *b);
    static bool SJFCompare(Process *a, Process *b);
};

// Function pointer to compare processes
typedef bool (*CompareProcesses)(Process *, Process *);


// Class to implement a priority queue
// It used to store the processes that are waiting to be executed
// In all the algorithms, the processes are sorted by their arrival time
class PriorityQueue
{
private:
    CompareProcesses compare;
    vector<Process *> waitingProcesses;

public:
    PriorityQueue(CompareProcesses compareProcesses);

    void push(Process *process, int t);
    void pop();
    Process *first();

    bool isEmpty();
    int size();

    // Heapify functions
    // They are used to maintain the heap property
    // The heap property is that the parent node is always greater than its children
    void heapifyFromBot(int rootIndex);
    void heapifyFromTop(int rootIndex);

    Process *&operator[](int i);
};
