#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "job_input.h"

#define MAX_LINE_LENGTH 256 // Maximum length for each line

JobNode* read_file(char* file_name, JobNode* (*adding_strategy)(JobNode* , Job))
{
    char line[MAX_LINE_LENGTH]; // Buffer for reading each line

    // Open the file in read mode
    FILE* file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
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
        traveler = adding_strategy(traveler, temp_job);
    }

    fclose(file);

    //TODO: Does head changes. I enabled in code. Deal with it.

    traveler = dummy->next;
    free(dummy);

    return traveler;
}
