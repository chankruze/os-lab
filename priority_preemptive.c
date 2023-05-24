/*
Author: chankruze (chankruze@gmail.com)
Created: Thu May 25 2023 02:40:30 GMT+0530 (India Standard Time)

Copyright (c) geekofia 2023 and beyond
*/

#include <stdbool.h>
#include <stdio.h>

// Process struct to hold process details
typedef struct process {
  int pid;
  int arrival_time;
  int burst_time;
  int priority;
  int remaining_time;
  int waiting_time;
  int turnaround_time;
} Process;

// Function to calculate waiting time, turn around time, average wait time and turn around time
void priorityScheduling(Process processes[], int n) {
  int total_time = 0;
  bool completed[n];
  int prev_priority = 0, current_process = -1;
  int completed_processes = 0;
  for (int i = 0; i < n; i++) {
    completed[i] = false;
    processes[i].remaining_time = processes[i].burst_time;
    processes[i].waiting_time = 0;
    processes[i].turnaround_time = 0;
  }
  while (completed_processes != n) {
    int min_priority = 9999;
    for (int i = 0; i < n; i++) {
      if (processes[i].arrival_time <= total_time && !completed[i] && processes[i].priority < min_priority) {
        min_priority = processes[i].priority;
        current_process = i;
      }
    }
    if (current_process == -1) {
      total_time++;
      continue;
    }
    if (current_process != -1 && prev_priority != processes[current_process].priority) {
      processes[current_process].waiting_time += total_time - processes[current_process].turnaround_time;
      prev_priority = processes[current_process].priority;
    }
    processes[current_process].remaining_time--;
    total_time++;
    if (processes[current_process].remaining_time == 0) {
      completed[current_process] = true;
      processes[current_process].turnaround_time = total_time - processes[current_process].arrival_time;
      completed_processes++;
    }
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
  }
  priorityScheduling(processes, n);
  return 0;
}
