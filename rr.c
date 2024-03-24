#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

struct Process {
    int process_number;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

// Function to sort processes according to their arrival time
void sortProcesses(struct Process *processes, int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    struct Process processes[MAX_PROCESSES];

    // Input process details
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_number = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort processes according to arrival time
    sortProcesses(processes, n);

    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                done = 0;
                if (processes[i].remaining_time > time_quantum) {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    current_time += processes[i].remaining_time;
                    processes[i].waiting_time = current_time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    total_waiting_time += processes[i].waiting_time;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    total_turnaround_time += processes[i].turnaround_time;

                    printf("%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", processes[i].process_number,
                           processes[i].arrival_time, processes[i].burst_time,
                           processes[i].waiting_time, processes[i].turnaround_time);
                }
            }
        }
        if (done == 1)
            break;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);

    return 0;
}
