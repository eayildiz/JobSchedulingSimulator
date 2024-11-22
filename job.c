#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "job.h"

JobNode* create_node(Job job);
result_list* create_result_node(const char* job_name);
bool is_smaller(int a, int b);
JobNode* update_head(JobNode* traveler, Job job);
void update_body(JobNode* traveler, Job job);

//TODO: Can be an array.
JobNode* form_job_queue(JobNode* head, JobNode* (*adding_strategy)(JobNode* , Job))
{
    JobNode* new_head = create_node(head->job);

    // Traverse the original list and insert each node into the sorted list
    JobNode* current = head->next;
    while (current != NULL) {
        new_head = adding_strategy(new_head, current->job);
        current = current->next;
    }

    return new_head;
}

//TODO: Can be an array.
result_list* form_result_list(JobNode* head)
{
    result_list* result_head = NULL; // Head of the result_list
    result_list* result_tail = NULL; // Tail pointer for appending nodes
    JobNode* current_job = head; // Pointer to traverse the JobNode list
    
    if(head != NULL)
    {
        result_head = create_result_node(current_job->job.task_name);
        result_tail = result_head;
        current_job = current_job->next;
    }

    while (current_job != NULL)
    {
        // Create a new result_list node with the task name
        result_list* new_node = create_result_node(current_job->job.task_name);

        // Append the new node to the result_list
        result_tail->next = new_node;
        result_tail = new_node;

        // Move to the next JobNode
        current_job = current_job->next;
    }

    return result_head; // Return the head of the result_list
}

/*Inserting new element to the sorted list from smaller to big by comparing nodes after traveler with priority.
*/
JobNode* add_by_priority(JobNode* traveler, Job job)
{
    JobNode* head = traveler;
    if(traveler == NULL)
    {
        perror("Error opening file");
        return NULL;
    }
    //Check first given node.
    if(is_smaller(job.priority, traveler->job.priority))
    {
        return update_head(traveler, job);
    }
    else
    {
        //Compare next node of traveler with job to insert to correct place.
        while(traveler->next != NULL && !is_smaller(job.priority, traveler->next->job.priority))
        {
            traveler = traveler->next;
        }
        update_body(traveler, job);
        return head;
    }
}

/*Inserting new element to the sorted list from smaller to big by comparing nodes after traveler with cpu_burst.
*/
JobNode* add_by_cpu_burst(JobNode* traveler, Job job)
{
    JobNode* head = traveler;
    if(traveler == NULL)
    {
        perror("Error opening file");
        return NULL;
    }
    //Check first given node.
    if(is_smaller(job.cpu_burst, traveler->job.cpu_burst))
    {
        return update_head(traveler, job);
    }
    else
    {
        //Compare next node of traveler with job to insert to correct place.
        while(traveler->next != NULL && !is_smaller(job.cpu_burst, traveler->next->job.cpu_burst))
        {
            traveler = traveler->next;
        }
        update_body(traveler, job);
        return head;
    }
}

JobNode* add_by_tail(JobNode* tail, Job job)
{
    JobNode* new_node = create_node(job);
    tail->next = new_node;
    return new_node;
}

JobNode* create_node(Job job)
{
    JobNode* new_node = (JobNode*)malloc(sizeof(JobNode));
    if (!new_node)
    {
        perror("Error allocating memory for new node");
        exit(EXIT_FAILURE);
    }
    new_node->job = job;
    new_node->previous = NULL;
    new_node->next = NULL;
    return new_node;
}

result_list* create_result_node(const char* job_name)
{
    result_list* new_node = (result_list*)malloc(sizeof(result_list));
    if (!new_node) {
        perror("Error allocating memory for result_list node");
        exit(EXIT_FAILURE);
    }
    strncpy(new_node->job_name, job_name, sizeof(new_node->job_name) - 1);
    new_node->job_name[sizeof(new_node->job_name) - 1] = '\0'; // Ensure null termination
    new_node->interval = NULL;
    new_node->num_of_intervals = 0;
    new_node->next = NULL;
    return new_node;
}

bool is_smaller(int a, int b)
{
    if(a < b)   return true;
    return false;
}

JobNode* update_head(JobNode* traveler, Job job)
{
    JobNode* new_node = create_node(job);
    new_node->next = traveler;
    traveler->previous = new_node;
    return new_node;
}

void update_body(JobNode* traveler, Job job)
{
    //Change next node of traveler with new node.
    JobNode* new_node = create_node(job);

    JobNode* temp = traveler->next;
    traveler->next = new_node;
    new_node->next = temp;
    new_node->previous = traveler;
    temp->previous = new_node;
}

// Function to display the linked list
void display_job_list(JobNode* head)
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

void display_result_list(result_list* head)
{
    result_list* current = head;
    while (current != NULL)
    {
        printf("%s -> [", current->job_name);
        for (int i = 0; i < current->num_of_intervals; i++)
        {
            printf("%d-%d", current->interval[i].starting_time, current->interval[i].ending_time);
            if (i < current->num_of_intervals - 1)
            {
                printf(", ");
            }
        }
        printf("]\n");
        current = current->next;
    }
}
