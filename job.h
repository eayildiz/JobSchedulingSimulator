typedef struct job
{
    char task_name[15];
    int priority;
    int cpu_burst;
}Job;

typedef struct interval
{
    int starting_time;
    int ending_time;
}interval;

typedef struct JobNode
{
    Job job;                // Job data
    struct JobNode* next;   // Pointer to the next node
}JobNode;

typedef struct result_list
{
    char job_name[15];
    interval* interval;
    struct result_list* next;   // Pointer to the next node
}result_list;

JobNode* form_job_queue(JobNode* head, JobNode* (*adding_strategy)(JobNode* , Job));
JobNode* add_by_priority(JobNode* traveler, Job job);
JobNode* add_by_cpu_burst(JobNode* traveler, Job job);
JobNode* add_by_tail(JobNode* tail, Job job);
result_list* form_result_list(JobNode* head);
