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
void display_list(JobNode* head)
{
    JobNode* traveler = head;
    printf("\nJobs in the linked list:\n");
    while (traveler != NULL)
    {
        printf("Task Name: %s, Priority: %d, CPU Burst: %d\n",
               traveler->job.task_name, traveler->job.priority, traveler->job.cpu_burst);
        traveler = traveler->next;
    }
}

result_list* run_by_SJF(JobNode* queue_head, result_list* result_head)
{
    int current_time = 0;
    while(queue_head != NULL)
    {
        //Consume the job and add interval to result.
        add_interval(queue_head->job.task_name, result_head, current_time, current_time + queue_head->job.cpu_burst);
        
        //Update time clock.
        current_time = current_time + queue_head->job.cpu_burst;
        
        //Next element
        JobNode* temp = queue_head;
        queue_head = queue_head->next;
        free(temp);
    }

    return result_head;
}

result_list* run_by_RR(JobNode* queue_head, result_list* result_head)
{
    int current_time = 0;
    const int quantum_time = 5;
    int executed_time;
    while(queue_head != NULL)
    {
        //Run the job quantum time or less unit time and add interval to result.
        if(queue_head->job.cpu_burst < quantum_time)
        {
            executed_time = queue_head->job.cpu_burst;
        }
        else
        {
            executed_time = quantum_time;
        }
        add_interval(queue_head->job.task_name, result_head, current_time, current_time + executed_time);

        //Update time clock.
        current_time = current_time + executed_time;
        
        //Update job cpu burst.
        queue_head->job.cpu_burst -= executed_time;
        //Check if job is finished.
        if(queue_head->job.cpu_burst <= 0)
        {
            //Remove current node.
            JobNode* temp = queue_head;
            queue_head = queue_head->next;
            temp->previous->next = queue_head;
            queue_head->previous = temp->previous;
            free(temp);
        }
        else
        {
            queue_head = queue_head->next;
        }
    }
    return result_head;
}

//TODO: Check if result_head updates.
void add_interval(char task_name[15], result_list* result_head, int starting_point, int ending_point)
{
    interval new_interval = {starting_point, ending_point};
    while(result_head != NULL && 0 != strcmp(task_name, result_head->job_name))
    {
        result_head = result_head->next;
    }

    if(result_head->num_of_intervals == 0)
    {
        result_head->interval = malloc(sizeof(interval));
    }
    else
    {
        result_head->interval = realloc(result_head->interval, (result_head->num_of_intervals + 1) * sizeof(interval));
    }
    *(result_head->interval + result_head->num_of_intervals) = new_interval;
    result_head->num_of_intervals++;
}