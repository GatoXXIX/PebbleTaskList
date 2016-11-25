
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

static Tasklist* createTasklist(int id);
static void freeTasksOfTasklist(Task *firstTask);
static Task* createTask(int target, double weight);

/* Public functions */

Data* createData() { 

  Data *d = (Data*)malloc(sizeof(Data*));    
  Tasklist *tl = createTasklist(1);
  
    if(d == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"There was not enough memory space for a new Data.\n");
        return NULL;
    }    
  d->tl = 1;
  d->firstTasklist = tl;
  
  return d;
}

void freeData(Data *d) {
    
    Tasklist *currentTasklist, *nextTasklist;
    
    if (d == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"The Data does not exist. There is no space allocated.\n");
        return;
    }
    
    currentTasklist = d->firstTasklist;
    while (currentTasklist != NULL) {
        
        freeTasksOfTasklist(currentTasklist->firstTask);
        nextTasklist = currentTasklist->nextTasklist;
        free(currentTasklist);
        currentTasklist = nextTasklist;
    }

    free(d);
    d = NULL;
}

void insertTask(Data *d, int source, int target, double weight) {
    
    Tasklist *currentTasklist;
    Task *currentTask;
    bool operationCompleted = false;
    
    if(d == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"Task can not be inserted. Data does not exist.\n");
    } else if (d->tl < target || target < 1) { 
        APP_LOG(APP_LOG_LEVEL_DEBUG,"Task can not be inserted. Check id of 'target'.\n");
    } else {
        currentTasklist = d->firstTasklist;
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
            APP_LOG(APP_LOG_LEVEL_DEBUG,"Task can not be inserted. Check id of 'source'.\n");
    }
}

void removeTask(Data *d, int source, int target) {
    
    Tasklist *currentTasklist;
    Task *currentTask, *preTask;
    bool TasklistFound = false;
    bool TaskFound = false;
    
    if (d == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"The Data does not exist. There is no space allocated.\n");
        return;
    } else if (d->tl >= target && target >= 1) {
        currentTasklist = d->firstTasklist;
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
            APP_LOG(APP_LOG_LEVEL_DEBUG,"Task doesn't exist. Check 'source'.\n");
    }
    if(!TaskFound)
        APP_LOG(APP_LOG_LEVEL_DEBUG,"Task doesn't exist. Check 'target'.\n");
}

void printData(Data *d) {
    
    Tasklist *currentTasklist;
    Task *currentTask;
    
     if (d == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"The Data does not exist. There is no space allocated.\n");
        return;
    } else {
        currentTasklist = d->firstTasklist;
        while(currentTasklist != NULL) {
            APP_LOG(APP_LOG_LEVEL_DEBUG,"%d. Tasklist", currentTasklist->id);
            
            currentTask = currentTasklist->firstTask;
            while(currentTask != NULL) {
                APP_LOG(APP_LOG_LEVEL_DEBUG," --> %d (w: %f)", 
                    currentTask->destTasklistId, currentTask->weight);
                currentTask = currentTask->nextTask;
            }
            currentTasklist = currentTasklist->nextTasklist;
        }   
    }
}

/* Returns weight, if Task exists - otherwise '0'. */
double doesTaskExist(Data *d, int source, int target) {
    
    Tasklist *currentTasklist;
    Task *currentTask;
    bool foundSource = false;
    
    if(d == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"The Data does not exist. There is no space allocated.\n");
        return 0;
    } else if (source > d->tl || source <= 0) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"The source parameter is invalid.\n");
        return 0;
    } else if (target > d->tl || target <= 0) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"The target parameter is invalid.\n");
        return 0;
    } else {
        currentTasklist = d->firstTasklist; 
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

/* Private functions */

static Tasklist* createTasklist(int id) {
    
  Tasklist *tl =(Tasklist*)malloc(sizeof(Tasklist));
  
  if (tl == NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG,"There was not enough memory space for a new Tasklist.\n");
    return NULL;
  }
  
  tl->id = id;
  tl->nextTasklist = NULL;
  tl->firstTask = NULL;
  
  return tl;
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
    Task *t = (Task*)malloc(sizeof(Task));
    
    if(t == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"There was not enough memory space for a new Task.\n");
        return NULL;
    }
    
    t->weight = weight;
    t->destTasklistId = target;
    t->nextTask = NULL;
    return t;
}

