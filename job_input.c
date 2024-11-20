#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256 // Maximum length for each line

typedef struct
{
    char task_name[15];
    int priority;
    int cpu_burst;
}Job;

typedef struct JobNode
{
    Job job;                // Job data
    struct JobNode* next;   // Pointer to the next node
}JobNode;

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

JobNode* add_new_job(JobNode* tail, Job job)
{
    JobNode* new_node = create_node(job);
    tail->next = new_node;
    return new_node;
}

int read_file(char* file_name, void())
{
    char line[MAX_LINE_LENGTH]; // Buffer for reading each line

    // Open the file in read mode
    FILE* file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    JobNode* dummy = create_node((Job){"", 0, 0});
    JobNode* traveler = dummy;

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        Job temp_job;

        // Parse the line into a Job struct
        if (sscanf(line, "%14s %d %d", temp_job.task_name, &temp_job.priority, &temp_job.cpu_burst) != 3)
        {
            fprintf(stderr, "Error parsing line: %s", line);
            continue;
        }
        traveler = add_new_job(traveler, temp_job);
    }

    fclose(file);

    return 0;
}
