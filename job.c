#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "job.h"

JobNode* create_node(Job job);
bool is_smaller(int a, int b);
JobNode* update_head(JobNode* traveler, Job job);
void update_body(JobNode* traveler, Job job);

JobNode* sorted_copy(JobNode* head, JobNode* (*adding_strategy)(JobNode* , Job))
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
    return new_node;
}

void update_body(JobNode* traveler, Job job)
{
    //Change next node of traveler with new node.
    JobNode* new_node = create_node(job);

    JobNode* temp = traveler->next;
    traveler->next = new_node;
    new_node->next = temp;
}
