#define MAX_TASK_NAME_LENGTH 50

typedef struct job
{
    char task_name[MAX_TASK_NAME_LENGTH];
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
    Job job;                    // Job data
    struct JobNode* previous;   // Pointer to the next node
    struct JobNode* next;       // Pointer to the next node
}JobNode;

typedef struct result_list
{
    char job_name[MAX_TASK_NAME_LENGTH];
    interval* interval;
    int num_of_intervals;
    struct result_list* next;   // Pointer to the next node
}result_list;

JobNode* form_job_queue(JobNode* head, JobNode* (*adding_strategy)(JobNode* , Job));
result_list* form_result_list(JobNode* head);
JobNode* add_by_priority(JobNode* traveler, Job job);
JobNode* add_by_cpu_burst(JobNode* traveler, Job job);
JobNode* add_by_tail(JobNode* tail, Job job);
JobNode* create_node(Job job);
void display_job_list(JobNode* head);
void display_result_list(result_list* head);
