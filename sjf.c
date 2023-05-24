/*
Author: chankruze (chankruze@gmail.com)
Created: Wed May 24 2023 21:21:59 GMT+0530 (India Standard Time)

Copyright (c) geekofia 2023 and beyond
*/

#include <limits.h>
#include <stdio.h>

// Process struct to hold process details
typedef struct process {
  int pid;
  int arrival_time;
  int burst_time;
  int waiting_time;
  int turnaround_time;
  int is_completed;
} Process;

// Function to calculate waiting time, turn around time, average wait time and turn around time
void sjf(Process processes[], int n) {
  int total_time = 0;
  int completed = 0;
  while (completed != n) {
    int shortest_job = -1;
    int shortest_burst_time = INT_MAX;
    for (int i = 0; i < n; i++) {
      if (processes[i].arrival_time <= total_time && !processes[i].is_completed && processes[i].burst_time < shortest_burst_time) {
        shortest_job = i;
        shortest_burst_time = processes[i].burst_time;
      }
    }
    if (shortest_job == -1) {
      total_time++;
      continue;
    }
    processes[shortest_job].waiting_time = total_time - processes[shortest_job].arrival_time;
    processes[shortest_job].turnaround_time = processes[shortest_job].waiting_time + processes[shortest_job].burst_time;
    total_time += processes[shortest_job].burst_time;
    processes[shortest_job].is_completed = 1;
    completed++;
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
  printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
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
  printf("Enter the arrival time and burst time for each process:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d:\n", i + 1);
    processes[i].pid = i + 1;
    printf("Arrival time: ");
    scanf("%d", &processes[i].arrival_time);
    printf("Burst time: ");
    scanf("%d", &processes[i].burst_time);
    processes[i].is_completed = 0;
  }
  sjf(processes, n);
  return 0;
}
