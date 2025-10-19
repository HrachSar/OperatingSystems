#include <stdio.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

void sort(Process *proc, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            	if (proc[j + 1].arrival_time < proc[j].arrival_time) {
                	Process temp = proc[j];
                	proc[j] = proc[j + 1];
                	proc[j + 1] = temp;
            	}
        }
   }
}

void execute(Process *proc, int n) {
    	int completion_time[n];
    	completion_time[0] = proc[0].arrival_time + proc[0].burst_time;

   	for (int i = 1; i < n; i++) {
        	completion_time[i] = (proc[i].arrival_time > completion_time[i - 1])
           		? proc[i].arrival_time + proc[i].burst_time
        	    : completion_time[i - 1] + proc[i].burst_time;
    	}

    	for (int i = 0; i < n; i++) {
        	proc[i].turnaround_time = completion_time[i] - proc[i].arrival_time;
        	proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
        	proc[i].response_time = proc[i].waiting_time; // For FCFS
    	}
}

int main() {
    	int n;
    	printf("Enter the number of processes: ");
    	scanf("%d", &n);
	double avg_tat = 0;
	double avg_wt = 0;
	double avg_rt = 0;
    	Process proc[n];
    	for (int i = 0; i < n; i++) {
        	printf("Enter the arrival time and burst time for process %d: ", i);
        	proc[i].pid = i + 1;
        	scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    	}

    	sort(proc, n);
    	execute(proc, n);
    	printf("=== First Come First Served (FCFS) ===\n");
    	for (int i = 0; i < n; i++){
		printf("| P%d\t", proc[i].pid);
    	}
    	printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    	for (int i = 0; i < n; i++) {
        	printf("%d\t%d\t%d\t%d\t%d\t%d\n",
          	proc[i].pid, proc[i].arrival_time, proc[i].burst_time,
        	proc[i].waiting_time, proc[i].turnaround_time, proc[i].response_time);
		avg_tat += proc[i].turnaround_time;
		avg_wt += proc[i].waiting_time;
		avg_rt += proc[i].response_time;
    	}
    	avg_tat /= n;
	avg_wt /= n;
	avg_rt /= n;
	printf("Average Turnaround Time: %.2f\n", avg_tat);
	printf("Average Waiting Time: %.2f\n", avg_wt);
	printf("Average Response Time: %.2f\n", avg_rt);
    	return 0;
}

