/*
Author: chankruze (chankruze@gmail.com)
Created: Thu May 25 2023 08:01:19 GMT+0530 (India Standard Time)

Copyright (c) geekofia 2023 and beyond
*/

#include <stdbool.h>
#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocated[MAX_PROCESSES][MAX_RESOURCES], int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max[i][j] - allocated[i][j];
    }
  }
}

bool isSafeState(int available[MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocated[MAX_PROCESSES][MAX_RESOURCES], int n, int m) {
  int need[MAX_PROCESSES][MAX_RESOURCES];
  bool finish[MAX_PROCESSES] = {false};
  int work[MAX_RESOURCES];
  int safeSequence[MAX_PROCESSES];
  int count = 0;

  for (int i = 0; i < m; i++) {
    work[i] = available[i];
  }

  calculateNeed(need, max, allocated, n, m);

  while (count < n) {
    bool found = false;
    for (int i = 0; i < n; i++) {
      if (!finish[i]) {
        bool canExecute = true;
        for (int j = 0; j < m; j++) {
          if (need[i][j] > work[j]) {
            canExecute = false;
            break;
          }
        }

        if (canExecute) {
          for (int j = 0; j < m; j++) {
            work[j] += allocated[i][j];
          }

          safeSequence[count++] = i;
          finish[i] = true;
          found = true;
        }
      }
    }

    if (!found) {
      break;
    }
  }

  if (count < n) {
    return false;  // System is in an unsafe state
  } else {
    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) {
      printf("%d ", safeSequence[i]);
    }
    printf("\n");
    return true;  // System is in a safe state
  }
}

int main() {
  int n, m;  // Number of processes and resources
  int max[MAX_PROCESSES][MAX_RESOURCES];
  int allocated[MAX_PROCESSES][MAX_RESOURCES];
  int available[MAX_RESOURCES];

  printf("Enter the number of processes: ");
  scanf("%d", &n);

  printf("Enter the number of resources: ");
  scanf("%d", &m);

  printf("Enter the maximum resource allocation for each process:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: ", i);
    for (int j = 0; j < m; j++) {
      scanf("%d", &max[i][j]);
    }
  }

  printf("Enter the currently allocated resources for each process:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: ", i);
    for (int j = 0; j < m; j++) {
      scanf("%d", &allocated[i][j]);
    }
  }

  printf("Enter the available resources: ");
  for (int i = 0; i < m; i++) {
    scanf("%d", &available[i]);
  }

  bool isSafe = isSafeState(available, max, allocated, n, m);
  if (isSafe) {
    printf("System is in a safe state.\n");
  } else {
    printf("System is in an unsafe state.\n");
  }

  return 0;
}
