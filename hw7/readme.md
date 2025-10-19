Homework Assignment: Process Scheduling Simulation (FCFS & SJF)

Objective:
You are tasked with writing a simple process scheduling simulator in C under Linux that implements two process scheduling algorithms:

    First Come First Served (FCFS)
    Shortest Job First (SJF)

Requirements:

    Implement a structure to represent processes, including attributes like process ID (PID), arrival time, and burst time.
    Simulate the scheduling of processes based on the two algorithms and compute the following for each process:
        Turnaround Time
        Waiting Time
        Response Time
    For each algorithm, you should have separate functions and call them inside the main function.
    Display the Gantt chart of execution order for each algorithm.

Steps

    Process Structure: Create a structure in C to represent a process with the following attributes:
        int pid: Process ID.
        int arrival_time: Time when the process arrives in the system.
        int burst_time: CPU burst time required by the process.
        int turnaround_time: Time taken from process arrival to its completion.
        int waiting_time: Time a process spends waiting in the queue.
        int response_time: Time from process arrival to the first execution (same as waiting time for non-preemptive algorithms).

    FCFS Algorithm:
        Sort the processes by arrival time.
        Execute processes in the order they arrive.
        Calculate waiting time, turnaround time, and response time for each process.

    SJF Algorithm (Non-preemptive):
        Sort processes by burst time (select the process with the shortest burst time first).
        If two processes have the same burst time, choose the one with the earlier arrival time.
        Calculate the same time metrics as above.

    Input and Output:
        Input: Ask the user to input the number of processes, followed by each process's arrival time and burst time.
        Output:
            Display the Gantt chart for each algorithm.
            Display the PID, arrival time, burst time, waiting time, turnaround time, and response time for each process.
            Calculate and display the average waiting time, turnaround time, and response time for each algorithm.

Sample Input:

Enter the number of processes: 4
Enter the arrival time and burst time for process 1: 0 8
Enter the arrival time and burst time for process 2: 1 4
Enter the arrival time and burst time for process 3: 2 9
Enter the arrival time and burst time for process 4: 3 5

Sample Output (FCFS):

=== First Come First Served (FCFS) ===
Gantt Chart: | P1 |   P2   |   P3   |   P4   |
PID     AT     BT     WT     TAT    RT
1       0      8      0      8      0
2       1      4      7      11     7
3       2      9      9      18     9
4       3      5      14     19     14

Average Waiting Time: 7.50
Average Turnaround Time: 14.00
Average Response Time: 7.50

Sample Output (SJF):

=== Shortest Job First (SJF) ===
Gantt Chart: | P2 | P4 |   P1   |   P3   |
PID     AT     BT     WT     TAT    RT
2       1      4      0      4      0
4       3      5      2      7      2
1       0      8      7      15     7
3       2      9      12     21     12

Average Waiting Time: 5.25
Average Turnaround Time: 11.75
Average Response Time: 5.25

Submission:

    Commit your C code and a README file explaining how to run your program. Share the link of the repo.
    Include input/output screenshots.

