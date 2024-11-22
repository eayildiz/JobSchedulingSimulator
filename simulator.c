#include <stdlib.h>
#include <stdio.h>
#include "job.h"

typedef enum cpu_scheduling_algorithm
{
    SHORTESTJOBFIRST,
    ROUNDROBIN,
    ROUNDROBINPRIORITY
}cpu_scheduling_algorithm;

void run_simulator(JobNode* head, cpu_scheduling_algorithm algorithm_choice)
{
    result_list* result = form_result_list(head);

    //Create job queue and run simulator based on choice.
    JobNode* job_queue;
    //TODO: Magic numbers
    switch (algorithm_choice)
    {
    case SHORTESTJOBFIRST:
        job_queue = form_job_queue(head, add_by_cpu_burst);
        break;
    case ROUNDROBIN:
        job_queue = form_job_queue(head, add_by_tail);
        break;
    case ROUNDROBINPRIORITY:
        job_queue = form_job_queue(head, add_by_priority);
        break;
    }
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