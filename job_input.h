#include "job.h"

JobNode* read_file(char* file_name, JobNode* (*adding_strategy)(JobNode* , Job));

