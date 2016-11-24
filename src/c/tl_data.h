#ifndef TL_DATA_H
#define TL_DATA_H

#include <time.h>

struct Task;
typedef 
    struct Task {
    int taskNr;
} Task;

Task* create_sample_data();
void delete_sample_data(Task *t);

#endif