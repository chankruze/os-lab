/*
Author: chankruze (chankruze@gmail.com)
Created: Wed May 24 2023 23:09:34 GMT+0530 (India Standard Time)

Copyright (c) geekofia 2023 and beyond
*/

#include <stdio.h>

// Process struct to hold process details
typedef struct process {
  int pid;
  int arrival_time;
  int burst_time;
  int priority;
  int waiting_time;
  int turnaround_time;
} Process;

// Function to calculate waiting time, turn around time, average wait time and turn around time
void priorityScheduling(Process processes[], int n) {
  // Sort the processes by priority
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (processes[i].priority > processes[j].priority) {
        Process temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }
  // Calculate waiting and turnaround time for the processes
  processes[0].waiting_time = 0;
  processes[0].turnaround_time = processes[0].burst_time;
  for (int i = 1; i < n; i++) {
    processes[i].waiting_time = processes[i - 1].turnaround_time;
    processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
  }
  // Calculate average waiting and turnaround time
  float avg_wait_time = 0, avg_turnaround_time = 0;
  for (int i = 0; i < n; i++) {
    avg_wait_time += processes[i].waiting_time;
    avg_turnaround_time += processes[i].turnaround_time;
  }
  avg_wait_time /= n;
  avg_turnaround_time /= n;
  // Print the results
  printf("PID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
  }
  printf("Average waiting time: %.2f\n", avg_wait_time);
  printf("Average turnaround time: %.2f\n", avg_turnaround_time);
}

// Driver code
int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  Process processes[n];
  printf("Enter the arrival time, burst time, and priority for each process:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d:\n", i + 1);
    processes[i].pid = i + 1;
    printf("Arrival time: ");
    scanf("%d", &processes[i].arrival_time);
    printf("Burst time: ");
    scanf("%d", &processes[i].burst_time);
    printf("Priority: ");
    scanf("%d", &processes[i].priority);
    processes[i].waiting_time = 0;
    processes[i].turnaround_time = 0;
  }
  priorityScheduling(processes, n);
  return 0;
}
