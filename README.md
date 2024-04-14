# Process Scheduling

## I. Introduction

This is Project 01 in our Operating System Class in HCMUS. Our task is writing a program to perform process scheduling according to the following requirement:
- The programming language is of your choice. 
- It can be run on the Windows operating system. 
- It can be executed via the command line using the following syntax: 
```
main.exe <INPUT_FILE> <OUTPUT_FILE>
```
For example: 
```
main.exe input.txt output.txt 
```
- The input and output files are both saved in text format (*.txt).
- The input and output files must follow syntax mentioned in session II. <br>
**HOW TO RUN PROGRAM**
- First, Run this code in vscode terminal to create exe file
```
g++ Source-Code/*.cpp -o main.exe
```
- Then, Run this code to run our program
```
./main.exe input.txt output.txt
```
## II. Syntax
### 1. Syntax of the input file
- The first line: an integer from 1 to 4 representing the scheduling algorithm

| #   |        Scheduling algorithm         |
| --- | :---------------------------------: |
| 1   |    FCFS (First Come First Serve)    |
| 2   |          RR (Round Robin)           |
| 3   |      SJF (Shortest Job First)       |
| 4   | SRTN (Shortest Remaining Time Next) |

- In case of the Round Robin scheduling algorithm, the second line is a positive integer 
representing the time quantum. 
- The next line: a positive integer N representing the number of processes to be 
scheduled, up to maximum of 4 processes. 
- The following N lines: each line describes the scheduling information of a process with the syntax:
```
<Arrival time in Ready Queue> [<CPU Burst Time> <Resource Usage Time>] 
```
- It is known that:
    - In the scheduling table, each process can use CPU and R multiple times, but 
up to a maximum of 3 times for each (CPU/R)
    - In the scheduling table, a process may complete earlier than other processes. 
This means that the number of CPU and R usages for each process is 
different.
    - The system only has one resource R. The scheduling algorithm on resource 
R is always FCFS. 
    - Give pripority to new processes in case of conflict in the entrance of Ready 
Queue.

**Example:** \
*FCFS/SJF/SRTN:* \
1 \
3 \
0 5 3 4 \
1 4 \
2 3 3 

| #   | Arrival Time | CPU | R   |  CPU  |
| --- | ------------ | --- | --- | :---: |
| P1  | 0            | 5   | 3   |   4   |
| P2  | 1            | 4   |     |       |
| P3  | 2            | 3   | 3   |       |

*Round Robin:* \
2 \
3 \
4 \
0 5 3 4 \
2 4 \
5 3 3 \
3 6 2 3 8 1

| #   | Arrival Time | CPU | R   | CPU | R   |  CPU  |
| --- | ------------ | --- | --- | --- | --- | :---: |
| P1  | 0            | 5   | 3   | 4   |     |       |
| P2  | 2            | 4   |     |     |     |       |
| P3  | 5            | 3   | 3   |     |     |       |
| P4  | 3            | 6   | 2   | 3   | 8   |   1   |

### 2. Syntax of the output file
- The first line: an integer sequence separated by a single whitespace, represents the Gantt chart of the process scheduling on the CPU. Note that the numbers 1, 2, 3, 4 represent processes P1, P2, P3, P4; and a hyphen ( _ ) denotes the time slot during which no process is using the CPU.
- The second line: has a similar structure to the first line, but it represents the 
scheduling on the resource R. 
- The third line: an integer sequence separated by a single whitespace, represents the turn-around time of all processes.
- The fourth line: an integer sequence separated by a single whitespace, represents 
the waiting time of all processes.

**Example:** 
| Input                             | Output                                                                               |
| --------------------------------- | ------------------------------------------------------------------------------------ |
| 1<br>3<br>0 5 3 4<br>1 4<br>2 3 3 | 1 1 1 1 1 2 2 2 2 3 3 3 1 1 1 1<br>_ _ _ _ _ 1 1 1 _ _ _ _ 3 3 3<br>16 8 13<br>4 4 7 |

It means: 
|          | 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  | 11  | 12  | 13  | 14  | 15  |
| ------- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| **CPU** | P1  | P1  | P1  | P1  | P1  | P2  | P2  | P2  | P2  | P3  | P3  | P3  | P1  | P1  | P1  | P1  |
| **R**   |     |     |     |     |     | P1  | P1  | P1  |     |     |     |     | P3  | P3  | P3  |     |

|     | Turn-around Time | Waiting Time |
| --- | ---------------- | :----------: |
| P1  | 16               |      4       |
| P2  | 8                |      4       |
| P3  | 13               |      7       |

## III. Project Organization
The folder contains:
- **Source-Code** folder: the entire source code of the program, remove 
all irrelevant subfolders to reduce the size. 
- **Test cases** folder: nearly 50 test cases for 4 algorithms
- **main.exe** file: a executive program that can be run via the 
command line on Windows.
- **input.txt** file: a sample input file that your program can be executed. 
- **output.txt** file: a sample output file that your program writes out corresponding to the input file above.