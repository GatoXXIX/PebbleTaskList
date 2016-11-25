/* Author:        Gartenlehner Daniel */
/* Enrolment nr.: S1510307010         */
/* Exercise:      SWO32A03BB          */
/* Created on:    01.11.2016          */ 
/* Semester:      WS 16/17            */
/* FileName:      xxxxxxxx.c          */

#include <stdio.h>
#include <stdlib.h>
#include <pebble.h>
#include "tl_data.h"

/* Internal Prototypes */

static void appendTasklist(Data *g, int id);
static Tasklist* createTasklist(int id);
static void freeTasksOfTasklist(Task *firstTask);
static Task* createTask(int target, double weight);

/* Public functions */

Data* createData(int n) { 
    
    int i;
    Data *g = (Data*)malloc(sizeof(Data*));
    
    if(n <= 0) {
        printf("The input value 'n' should be greater than 0.\n");
        return NULL;
    }
    
    if(g == NULL) {
        printf("There was not enough memory space for a new Data.\n");
        return NULL;
    }
    
    g->n = n;
    g->firstTasklist = createTasklist(1);
    
    for(i = 2; i <= n ; i++)
        appendTasklist(g, i);   
    
    return g;
}

void freeData(Data *g) {
    
    Tasklist *currentTasklist, *nextTasklist;
    
    if (g == NULL) {
        printf("The Data does not exist. There is no space allocated.\n");
        return;
    }
    
    currentTasklist = g->firstTasklist;
    while (currentTasklist != NULL) {
        
        freeTasksOfTasklist(currentTasklist->firstTask);
        nextTasklist = currentTasklist->nextTasklist;
        free(currentTasklist);
        currentTasklist = nextTasklist;
    }

    free(g);
    g = NULL;
}

void insertTask(Data *g, int source, int target, double weight) {
    
    Tasklist *currentTasklist;
    Task *currentTask;
    bool operationCompleted = false;
    
    if(g == NULL) {
        printf("Task can not be inserted. Data does not exist.\n");
    } else if (g->n < target || target < 1) { 
        printf("Task can not be inserted. Check id of 'target'.\n");
    } else {
        currentTasklist = g->firstTasklist;
        while(currentTasklist != NULL && operationCompleted != true) {
            if(currentTasklist->id == source) {
                currentTask = currentTasklist->firstTask;
            
                if(currentTask == NULL) {
                    /* Add first Task to the current Tasklist */    
                    currentTasklist->firstTask = createTask(target, weight);
                } else {
                    /* Add new Task to the last existing Task */
                    while(currentTask->nextTask != NULL) {
                        currentTask = currentTask->nextTask;
                    }
                    currentTask->nextTask = createTask(target, weight);
                }
                operationCompleted = true;     
            } else {
                currentTasklist = currentTasklist->nextTasklist;
            }
        } /* while */
        
        if(!operationCompleted)
            printf("Task can not be inserted. Check id of 'source'.\n");
    }
}

void removeTask(Data *g, int source, int target) {
    
    Tasklist *currentTasklist;
    Task *currentTask, *preTask;
    bool TasklistFound = false;
    bool TaskFound = false;
    
    if (g == NULL) {
        printf("The Data does not exist. There is no space allocated.\n");
        return;
    } else if (g->n >= target && target >= 1) {
        currentTasklist = g->firstTasklist;
        while(currentTasklist != NULL && TasklistFound == false) {
            if(currentTasklist->id == source) {
                currentTask = currentTasklist->firstTask;
                preTask = currentTasklist->firstTask; /* Pseudo-initialize */
                if(currentTask != NULL) {
                    if(currentTask->destTasklistId == target) {
                        /* case that first Task of Tasklist is the target */
                        currentTasklist->firstTask = currentTask->nextTask;
                        free(currentTask);
                        TaskFound = true; /* For validation only */
                    } else {
                        /* case that first Task of Tasklist is not the target */
                        while(currentTask != NULL 
                              && currentTask->destTasklistId != target) {
                            preTask = currentTask;
                            currentTask = currentTask->nextTask;            
                        }
                        if(currentTask != NULL) {
                            preTask->nextTask = currentTask->nextTask;
                            free(currentTask);    
                            TaskFound = true; /* For validation only */
                        }
                    }
                } /* if */
                TasklistFound = true;
            } else {    
                currentTasklist = currentTasklist->nextTasklist;
            }
        } /* while */
        
        if(!TasklistFound)
            printf("Task doesn't exist. Check 'source'.\n");
    }
    if(!TaskFound)
        printf("Task doesn't exist. Check 'target'.\n");
}

void printData(Data *g) {
    
    Tasklist *currentTasklist;
    Task *currentTask;
    
     if (g == NULL) {
        printf("The Data does not exist. There is no space allocated.\n");
        return;
    } else {
        currentTasklist = g->firstTasklist;
        while(currentTasklist != NULL) {
            printf("%d. Tasklist", currentTasklist->id);
            
            currentTask = currentTasklist->firstTask;
            while(currentTask != NULL) {
                printf(" --> %d (w: %f)", 
                    currentTask->destTasklistId, currentTask->weight);
                currentTask = currentTask->nextTask;
            }
            printf("\n");
            currentTasklist = currentTasklist->nextTasklist;
        }   
    }
}

/* Returns weight, if Task exists - otherwise '0'. */
double doesTaskExist(Data *g, int source, int target) {
    
    Tasklist *currentTasklist;
    Task *currentTask;
    bool foundSource = false;
    
    if(g == NULL) {
        printf("The Data does not exist. There is no space allocated.\n");
        return 0;
    } else if (source > g->n || source <= 0) {
        printf("The source parameter is invalid.\n");
        return 0;
    } else if (target > g->n || target <= 0) {
        printf("The target parameter is invalid.\n");
        return 0;
    } else {
        currentTasklist = g->firstTasklist; 
        while(currentTasklist != NULL && foundSource == false) {
            if(currentTasklist->id == source) {
                currentTask = currentTasklist->firstTask;
                while(currentTask != NULL) {
                    if(currentTask->destTasklistId == target) {
                        /* Found source & target combination */
                        return currentTask->weight; 
                    } else {
                        currentTask = currentTask->nextTask;
                    }
                }
                foundSource = true; /* Exit loop */
            } else {
                currentTasklist = currentTasklist->nextTasklist;
            }
        }
        /* Task not found */
        return 0;
    }
}

int getSizeOfData(Data *g) {
    
    if(g == NULL) {
        printf("The Data does not exist. There is no space allocated.\n");
        return 0;
    } else {
        return g->n;
    }
}

/* Private functions */

static void appendTasklist(Data *g, int id) {
    Tasklist *current = g->firstTasklist;
    while(current->nextTasklist != NULL) {
        current = current->nextTasklist;
    }
    current->nextTasklist = createTasklist(id);
}

static Tasklist* createTasklist(int id) {
  Tasklist *n = (Tasklist*)malloc(sizeof(Tasklist));
  
  if (n == NULL) {
    printf("There was not enough memory space for a new Tasklist.\n");
    return NULL;
  }
  
  n->id = id;
  n->nextTasklist = NULL;
  n->firstTask = NULL;
  return n;
}

static void freeTasksOfTasklist(Task *firstTask) {
    
    Task *currentTask, *nextTask; 
    currentTask = firstTask;
    
    while(currentTask != NULL) {
        nextTask = currentTask->nextTask;
        free(currentTask);
        currentTask = nextTask;
    }
}

static Task* createTask(int target, double weight) {
    Task *e = (Task*)malloc(sizeof(Task));
    
    if(e == NULL) {
        printf("There was not enough memory space for a new Task.\n");
        return NULL;
    }
    
    e->weight = weight;
    e->destTasklistId = target;
    e->nextTask = NULL;
    return e;
}

