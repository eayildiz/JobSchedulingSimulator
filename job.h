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

JobNode* sorted_copy(JobNode* head, JobNode* (*adding_strategy)(JobNode* , Job));
JobNode* add_by_priority(JobNode* traveler, Job job);
JobNode* add_by_cpu_burst(JobNode* traveler, Job job);
JobNode* add_by_tail(JobNode* tail, Job job);
