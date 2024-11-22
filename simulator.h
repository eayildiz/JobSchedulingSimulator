typedef enum cpu_scheduling_algorithm
{
    SHORTESTJOBFIRST,
    ROUNDROBIN,
    ROUNDROBINPRIORITY
}cpu_scheduling_algorithm;

void run_simulator(JobNode* head, cpu_scheduling_algorithm algorithm_choice);
