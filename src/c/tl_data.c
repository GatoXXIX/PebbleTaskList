#include <pebble.h>
#include <stdio.h>
#include <stdlib.h>
#include "tl_data.h"

struct Task;

Task* create_sample_data() { 
    
    Task *t = (Task*)malloc(sizeof(Task*));
    t->taskNr = 1000;
    return t;
}

void delete_sample_data(Task *t) {
    
    free(t);
    t = NULL;
}
