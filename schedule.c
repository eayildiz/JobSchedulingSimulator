#include <stdio.h>
#include "job.h"
#include "job_input.h"
#include "simulator.h"

#define MAX_TASK_NAME_LENGTH 15

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <file_name> <algorithm>\n", argv[0]);
        return 1;
    }

    // Validate the file name length
    if (strlen(argv[1]) > MAX_TASK_NAME_LENGTH)
    {
        fprintf(stderr, "Error: File name must not exceed %d characters.\n", MAX_TASK_NAME_LENGTH);
        return 1;
    }

    // Validate the algorithm
    const char* algorithm = argv[2];
    if (strcmp(algorithm, "SJF") != 0 && strcmp(algorithm, "RR") != 0 && strcmp(algorithm, "RRP") != 0)
    {
        fprintf(stderr, "Error: Algorithm must be one of 'SJF', 'RR', or 'RRP'.\n");
        return 1;
    }

    // Read jobs from the file
    JobNode* job_list = read_file(argv[1]);

    // Display the jobs (for verification purposes)
    display_jobs(job_list);

    // Call the appropriate scheduling algorithm
    if (strcmp(algorithm, "SJF") == 0)
    {
        run_simulator(job_list, SHORTESTJOBFIRST);
    }
    else if (strcmp(algorithm, "RR") == 0)
    {
        run_simulator(job_list, ROUNDROBIN);
    }
    else if (strcmp(algorithm, "RRP") == 0)
    {
        run_simulator(job_list, ROUNDROBINPRIORITY);
    }

    // Free the job list
    free_job_list(job_list);

    return 0;
}