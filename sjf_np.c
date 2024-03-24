#include<stdio.h>
#include<stdlib.h>

#define MAX_PROCESSES 100

struct Process {
    int process_number;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completed; // Flag to track completion status
};

// Function to sort processes according to their burst time
void sortProcesses(struct Process *processes, int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
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
        processes[i].completed = 0;
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int current_time = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    while (1) {
        int shortest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                if (shortest == -1 || processes[i].burst_time < processes[shortest].burst_time) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            int min_arrival_time = __INT_MAX__;
            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && processes[i].arrival_time < min_arrival_time) {
                    min_arrival_time = processes[i].arrival_time;
                }
            }
            current_time = min_arrival_time;
            continue;
        }

        processes[shortest].waiting_time = current_time - processes[shortest].arrival_time;
        processes[shortest].turnaround_time = processes[shortest].waiting_time + processes[shortest].burst_time;

        printf("%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\n", processes[shortest].process_number,
               processes[shortest].arrival_time, processes[shortest].burst_time,
               processes[shortest].waiting_time, processes[shortest].turnaround_time);

        total_waiting_time += processes[shortest].waiting_time;
        total_turnaround_time += processes[shortest].turnaround_time;
        current_time += processes[shortest].burst_time;
        processes[shortest].completed = 1;

        int flag = 1;
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            break;
        }
    }

    printf("\nAverage Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);

    return 0;
}
