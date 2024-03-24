#include<stdio.h>
#include<stdlib.h>

#define MAX_PROCESSES 100

struct Process {
    int process_number;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
};

// Function to sort processes according to their arrival time and burst time
void sortProcesses(struct Process *processes, int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            } else if (processes[j].arrival_time == processes[j + 1].arrival_time) {
                if (processes[j].burst_time > processes[j + 1].burst_time) {
                    temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[MAX_PROCESSES];

    // Input process details
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].process_number = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort processes according to arrival time and burst time
    sortProcesses(processes, n);

    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;
    int completed_processes = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    while (completed_processes < n) {
        int min_burst_time = MAX_PROCESSES + 1;
        int next_process = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_burst_time) {
                    min_burst_time = processes[i].remaining_time;
                    next_process = i;
                }
            }
        }
        if (next_process == -1) {
            printf("CPU Idle\t%d\t\t\t\t\t\t\t\t\t%d\n", current_time, processes[completed_processes].arrival_time);
            current_time = processes[completed_processes].arrival_time;
        } else {
            processes[next_process].remaining_time--;

            if (processes[next_process].remaining_time == 0) {
                processes[next_process].turnaround_time = current_time + 1 - processes[next_process].arrival_time;
                processes[next_process].waiting_time = processes[next_process].turnaround_time - processes[next_process].burst_time;
                total_waiting_time += processes[next_process].waiting_time;
                total_turnaround_time += processes[next_process].turnaround_time;

                printf("%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", processes[next_process].process_number,
                       processes[next_process].arrival_time, processes[next_process].burst_time,
                       processes[next_process].waiting_time, processes[next_process].turnaround_time);

                completed_processes++;
            }
        }
        current_time++;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);

    return 0;
}
