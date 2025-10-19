#include <stdio.h>
#include <limits.h>

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
                if (proc[j + 1].burst_time < proc[j].burst_time) {
                        Process temp = proc[j];
                        proc[j] = proc[j + 1];
                        proc[j + 1] = temp;
                }
        }
   }
}
void execute(Process *proc, int n){
	int completion_time[n];
	int completed[n];
	short found = 0;
	for(int i = 0; i < n; i++){
		completion_time[i] = 0;
		completed[i] = 0;
	}
	int curr_time = 0;
	int count = 0;
	while (1){
		found = 0;
		for(int i = 0; i < n; i++){
			if(proc[i].arrival_time <= curr_time && !completed[i]){
				completion_time[i] = curr_time + proc[i].burst_time;
				curr_time += proc[i].burst_time;
				completed[i] = 1;
				found = 1;
				count++;
				break;
			}
		}
		if(count == n)
			break;
		//Handle idle state
		//Without idle state check I solved in O(n) time 
		else if(!found){
			int next_time = INT_MAX;
			for(int i = 0; i < n; i++){
				if(proc[i].arrival_time < next_time && !completed[i])
					next_time = proc[i].arrival_time;
			}
			curr_time = next_time;
		}
	}
	for(int i = 0; i < n; i++){
		proc[i].turnaround_time = completion_time[i] - proc[i].arrival_time;
		proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
		proc[i].response_time = proc[i].waiting_time;
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
    	printf("=== Shortest Job First (SJF) ===\n");
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
