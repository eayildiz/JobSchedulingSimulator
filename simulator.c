#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "job.h"
#include "simulator.h"

JobNode* get_next_job_RRP(JobNode* current_job, JobNode* priority_head);
void add_interval(char task_name[15], result_list* result_head, int starting_point, int ending_point);
result_list* run_by_SJF(JobNode* queue_head, result_list* result_head);
result_list* run_by_RR(JobNode* queue_head, result_list* result_head);
result_list* run_by_RRP(JobNode* queue_head, result_list* result_head);

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
        printf("Flag_runsim_between\n");
        result = (result_list*)run_by_SJF(job_queue, result);
        break;
    case ROUNDROBIN:
        job_queue = form_job_queue(head, add_by_tail);
        printf("Flag_runsim_between\n");
        display_job_list(job_queue);
        result = (result_list*)run_by_RR(job_queue, result);
        break;
    case ROUNDROBINPRIORITY:
        job_queue = form_job_queue(head, add_by_priority);
        display_job_list(job_queue);
        result = (result_list*)run_by_RRP(job_queue, result);
        break;
    }
    printf("Flag_run_sim_out\n");

    display_result_list(result);
}

result_list* run_by_SJF(JobNode* queue_head, result_list* result_head)
{
    printf("Flag_runSJF_1\n");
    int current_time = 0;
    while(queue_head != NULL)
    {
        printf("Flag_runSJF_2\n");
        //Consume the job and add interval to result.
        add_interval(queue_head->job.task_name, result_head, current_time, current_time + queue_head->job.cpu_burst);
        
        //Update time clock.
        current_time = current_time + queue_head->job.cpu_burst;
        
        //Next element
        JobNode* temp = queue_head;
        queue_head = queue_head->next;
        free(temp);
    }
    printf("Flag_runbySJF_out\n");

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
            if(queue_head->next == queue_head)
            {
        printf("Flag_rr_next_0\n");
                free(queue_head);
                return result_head;
            }
            else
            {
        printf("Flag_rr_next_1\n");
                //Remove current node.
                JobNode* temp = queue_head;
                temp->previous->next = temp->next;
        printf("Flag_rr_next_2\n");
                temp->next->previous = temp->previous;
                queue_head = queue_head->next;
                free(temp);
            }
        }
        else
        {
            queue_head = queue_head->next;
    printf("Flag_rr_next_3\n");
        }
    printf("Flag_rr_endofwhile\n");
        printf("queue_head: %p\n", queue_head);
    }
    return result_head;
}

result_list* run_by_RRP(JobNode* queue_head, result_list* result_head)
{
    JobNode* priority_head = queue_head;
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
        printf("Flag_rrp_update_1\n");
        //Check if job is finished.
        if(queue_head->job.cpu_burst <= 0)
        {
            //Remove current node.
            JobNode* temp = queue_head;
            if(queue_head == priority_head)
            {
                if(priority_head->next != NULL)
                {
                    priority_head = priority_head->next;    
        printf("Flag_rrp_update_2\n");
                }
                else    //Everything done.
                {
                    free(temp);
        printf("Flag_rrp_update_3\n");
                    return result_head;
                }
            }
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            queue_head = get_next_job_RRP(queue_head, priority_head);
            free(temp);
        printf("Flag_rrp_update_4\n");
        }
        else
        {
        printf("Flag_rrp_update_5\n");
            queue_head = get_next_job_RRP(queue_head, priority_head);
        }

    }
    return result_head;
}

JobNode* get_next_job_RRP(JobNode* current_job, JobNode* priority_head)
{
    if(current_job->next->job.priority == priority_head->job.priority)
    {
        current_job = current_job->next;
    }
    else
    {
        current_job = priority_head;
    }
    return current_job;
}

//TODO: Check if result_head updates.
void add_interval(char task_name[15], result_list* result_head, int starting_point, int ending_point)
{
    printf("Flag_interval\n");
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
        printf("Flag_interval_1\n");
        result_head->interval = realloc(result_head->interval, (result_head->num_of_intervals + 1) * sizeof(interval));
    }
    printf("Flag_interval_2\n");
    *(result_head->interval + result_head->num_of_intervals) = new_interval;
    printf("Flag_interval_3\n");
    result_head->num_of_intervals += 1;
}