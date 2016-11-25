/* Author:        Gartenlehner Daniel */
/* Enrolment nr.: S1510307010         */
/* Exercise:      SWO32A04BB          */
/*                Pebble Projekt      */
/* Created on:    24.11.2016          */ 
/* Semester:      WS 16/17            */
/* FileName:      tl_data.c           */

#include <stdio.h>
#include <stdlib.h>
#include <pebble.h>
#include "tl_data.h"

/* Internal Prototypes */

static Tasklist* createTasklist(int id);
static void freeTasksOfTasklist(Task *firstTask);
static Task* createTask();

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

void insertTask(Data *d, int taskNr) {
    
  Tasklist *currentTasklist;
  Task *currentTask;
  bool operationCompleted = false;
    
  if(d == NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG,"Task can not be inserted. Data does not exist.\n");
  } else {
    currentTasklist = d->firstTasklist;
    while(currentTasklist != NULL && operationCompleted != true) {
      if(currentTasklist->id == taskNr) {
        currentTask = currentTasklist->firstTask;
          if(currentTask == NULL) {
          /* Add first Task to the current Tasklist */    
            currentTasklist->firstTask = createTask();
          } else {
            /* Add new Task to the last existing Task */
            while(currentTask->nextTask != NULL) {
              currentTask = currentTask->nextTask;
            }
            currentTask->nextTask = createTask();
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

void removeTask(Data *d, int taskNr) {
    
  Tasklist *currentTasklist;
  Task *currentTask, *preTask;
  bool TasklistFound = false;
  bool TaskFound = false;
    
  if (d == NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG,"The Data does not exist. There is no space allocated.\n");
    return;
  } else {
    currentTasklist = d->firstTasklist;
    while(currentTasklist != NULL && TasklistFound == false) {
      if(currentTasklist->id == taskNr) {
        currentTask = currentTasklist->firstTask;
        preTask = currentTasklist->firstTask; /* Pseudo-initialize */
        if(currentTask != NULL) {             
          while(currentTask != NULL) {
            preTask = currentTask;
            currentTask = currentTask->nextTask;            
          }
          if(currentTask != NULL) {
            preTask->nextTask = currentTask->nextTask;
            free(currentTask);    
            TaskFound = true; /* For validation only */
          }          
        }
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
                currentTask = currentTask->nextTask;
            }
            currentTasklist = currentTasklist->nextTasklist;
        }   
    }
}

bool doesTaskExist(Data *d, int taskNr) {
    
    Tasklist *currentTasklist;
    Task *currentTask;
    
    if(d == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"The Data does not exist. There is no space allocated.\n");
        return true;
    } else {
        currentTasklist = d->firstTasklist; 
        while(currentTasklist != NULL) {
            if(currentTasklist->id == taskNr) {
               return true;
             } else {
               currentTask = currentTask->nextTask;
             }
        }
        /* Task not found */
        return false;
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

static Task* createTask(int target) {
    Task *t = (Task*)malloc(sizeof(Task));
    
    if(t == NULL) {
        APP_LOG(APP_LOG_LEVEL_DEBUG,"There was not enough memory space for a new Task.\n");
        return NULL;
    }
    
    t->nextTask = NULL;
    return t;
}

