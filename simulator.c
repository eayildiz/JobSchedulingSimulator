#include <stdlib.h>
#include <stdio.h>
#include "job.h"

void run_simulator(JobNode* head)
{
    //Create job lists for different algorithms.
    JobNode* SJF_head = sorted_copy(head, add_by_cpu_burst);
    JobNode* RRP_head = sorted_copy(head, add_by_priority);

    //
}

// Function to display the linked list
void display_list(JobNode* head) {
    JobNode* traveler = head;
    printf("\nJobs in the linked list:\n");
    while (traveler != NULL) {
        printf("Task Name: %s, Priority: %d, CPU Burst: %d\n",
               traveler->job.task_name, traveler->job.priority, traveler->job.cpu_burst);
        traveler = traveler->next;
    }
}